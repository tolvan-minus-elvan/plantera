#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>
#include <stdint.h>
#include <ESPmDNS.h> // connect to server using "hostname".local, awesome!

#include "prot.h" // generated file
//#include "DataProtocol.h"
#include "setup_page.h" // setup page, using xxd
#include "main_page.h" // main page, using xxd

#define WIFI_PASSWORD_LEN 64
#define WIFI_SSID_LEN 64
#define WIFI_PASSWORD_ADDRESS (WIFI_SSID_LEN + WIFI_SSID_ADDRESS)
#define WIFI_SSID_ADDRESS 0
#define HOTSPOT_PASSWORD "plantera"
#define HOTSPOT_SSID "plantera"

#define HOSTNAME "plantera"

#define SERVER_TIMEOUT 10000 // 10 seconds
#define EEPROM_SIZE (WIFI_PASSWORD_ADDRESS + WIFI_PASSWORD_LEN + sizeof(plant_config) * AMOUNT_OF_PLANTS)

#define MESSAGE_BUF_LEN 256

#define PLANTS_ADDRESS 128

#define MAX_WATER_ATTEMPTS 15

#define NOT_CONNECTED_LIMIT 15

#define HUMIDITY_SENSOR_MIN 0
#define HUMIDITY_SENSOR_MAX 4095

#define PUMP_TIME 5000

#define INIT_AP_PIN 32

#define AMOUNT_OF_PLANTS 3

#define UPDATE_DELAY 1000 * 20 * 1 // every 5 minutes

struct plant_config {
  float lower_limit;
  float upper_limit;
  bool is_connected;
};

struct plant_base {
  uint8_t sensor_measure_pin;
  uint8_t pump_control_pin;
  bool currently_watering = false;;
  plant_config config;
  uint8_t water_attempts = 0;
  bool inverted = false;
};

char wifi_password[WIFI_PASSWORD_LEN];
char wifi_ssid[WIFI_SSID_LEN];
bool hotspot_active = false;
bool server_active = false;
struct plant_base plants[AMOUNT_OF_PLANTS];
WiFiServer server;
WiFiClient client;

void answerGet(uint8_t* buf, uint16_t len) {
  char len_buf[10];
  itoa(len, len_buf, 10);
  client.write("HTTP/1.1 200 OK\r\n");
  client.write("Content-Type: text/html\r\n");
  client.write("Content-Length: ");
  client.write(len_buf, strlen(len_buf));
  client.write("\r\n");
  client.write("Connection: close\r\n");
  client.write("\r\n");
  client.write(buf, len);
  client.stop();
}

void answerPost(uint8_t* buf, uint16_t len) {
  char len_buf[10];
  itoa(len, len_buf, 10);
  client.write("HTTP/1.1 200 OK\r\n");
  client.write("Content-Type: application/octet-stream\r\n");
  client.write("Content-Length: ");
  client.write(len_buf, strlen(len_buf));
  client.write("\r\n");
  client.write("Connection: close\r\n");
  client.write("\r\n");
  client.write(buf, len);
}

void updateServer() {
  // web server
  client = server.available();
  uint8_t line[MESSAGE_BUF_LEN];
  uint8_t first_line[MESSAGE_BUF_LEN];
  uint32_t socket_start = millis();
  while (client && client.connected() && millis() - socket_start < SERVER_TIMEOUT) {
    if (!client.available()) continue;
    yield();
    // find first line
    uint8_t first_line_len = client.readBytesUntil('\n', first_line, sizeof(first_line));
    uint8_t len = 0;
    while (millis() - socket_start < SERVER_TIMEOUT) {
      yield();
      // read individual lines
      uint8_t line_len = client.readBytesUntil('\n', line, sizeof(line));
      char header[] = "Content-Length: ";
      if (memcmp(line, header, strlen(header)) == 0) {
        len = atoi((char*) (line + strlen(header)));
      }
      if (line_len == 1) {
        break;
      }
    }
    client.readBytes(line, len);
    if (memcmp(first_line, "GET", 3) == 0) {
      if (hotspot_active) {
        answerGet((uint8_t*) sites_setup_html, sizeof(sites_setup_html));
      } else {
        answerGet((uint8_t*) sites_main_html, sizeof(sites_main_html));
      }
    } else
    if (memcmp(first_line, "POST", 4) == 0) {
      Serial.write(line, len);
      prot::parse_message(line[0], line + 1);
    }
  }
  client.stop();
}

bool plant_connected(plant_base* plant) {
  return plant->config.is_connected;
}

float read_humidity(plant_base* plant) {
  int32_t raw_measurement = analogRead(plant->sensor_measure_pin);
  float humidity = (float) (raw_measurement - HUMIDITY_SENSOR_MIN) / (float) (HUMIDITY_SENSOR_MAX - HUMIDITY_SENSOR_MIN) * 100.0;
  return humidity;
}

void update_plant(plant_base* plant) {
  if (!plant_connected(plant)) return;

  float humidity = read_humidity(plant);
  if (humidity < plant->config.lower_limit) {
    plant->currently_watering = true;
  }

  if (humidity > plant->config.lower_limit) {
    plant->currently_watering = false;
  }

  if (plant->currently_watering) {
    plant->water_attempts += 1;
    if (plant->water_attempts > MAX_WATER_ATTEMPTS) {
      plant->config.is_connected = false;
    }
    digitalWrite(plant->pump_control_pin, !plant->inverted);
    uint32_t start = millis();
    while (millis() - start < PUMP_TIME){
      updateServer(); // I call this epic multi-tasking
      yield();
    }
    digitalWrite(plant->pump_control_pin, plant->inverted);
  }
}

void connect_to_wifi() {
  static uint32_t last_attempt = 0;
  //only try every 10 seconds
  if (millis() - last_attempt > 10000) {
    last_attempt = millis();
    WiFi.softAPdisconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);
    hotspot_active = false;
  }
}

void prot::rx(prot::wifi_config_from_web_to_plant msg) {
  memcpy(wifi_ssid, msg.get_SSID(), sizeof(wifi_ssid));
  memcpy(wifi_password, msg.get_password(), sizeof(wifi_password));
  EEPROM.writeBytes(WIFI_SSID_ADDRESS, wifi_ssid, WIFI_SSID_LEN);
  EEPROM.writeBytes(WIFI_PASSWORD_ADDRESS, wifi_password, WIFI_PASSWORD_LEN);
  EEPROM.commit();
  answerPost(nullptr, 0);
  connect_to_wifi();
}

void prot::rx(prot::configure_plant_from_web_to_plant msg) {
  if (msg.get_plant_id() >= AMOUNT_OF_PLANTS) return; // wtf

  plant_base* target = &plants[msg.get_plant_id()];
  target->config.lower_limit = msg.get_lower_limit();
  target->config.upper_limit = msg.get_upper_limit();
  target->config.is_connected = msg.get_is_connected();
  EEPROM.writeBytes(PLANTS_ADDRESS + sizeof(plant_config) * msg.get_plant_id(), &(target->config), sizeof(plant_config));
  EEPROM.commit();
  answerPost(nullptr, 0);
}

void prot::rx(prot::get_plant_info_from_web_to_plant msg) {
  if (msg.get_plant_id() >= AMOUNT_OF_PLANTS) return;
  prot::plant_info_from_plant_to_web response;
  plant_base plant = plants[msg.get_plant_id()];

  response.set_plant_id(msg.get_plant_id());
  response.set_is_connected(plant_connected(&plant));
  response.set_humidity(read_humidity(&plant));
  response.set_lower_limit(plant.config.lower_limit);
  response.set_upper_limit(plant.config.upper_limit);
  uint8_t buf[response.get_size() + 1];
  uint8_t index = 0;
  response.build_buf(buf, &index);
  answerPost(buf, index);
}

void setup() {
  Serial.begin(115200);
  //init plant

  plants[0].pump_control_pin = 13;
  plants[1].pump_control_pin = 12;
  plants[2].pump_control_pin = 26;
  plants[0].inverted = true;

  plants[0].sensor_measure_pin = 36;
  plants[1].sensor_measure_pin = 39;
  plants[2].sensor_measure_pin = 34;

  analogReadResolution(12);

  //init pins;
  pinMode(INIT_AP_PIN, INPUT_PULLUP);
  //pinMode(INIT_AP_PIN3, INPUT_PULLDOWN);
  for (uint8_t i = 0; i < AMOUNT_OF_PLANTS; i++) {
    pinMode(plants[i].sensor_measure_pin, INPUT);
    pinMode(plants[i].pump_control_pin, OUTPUT);
    digitalWrite(plants[i].pump_control_pin, !plants[i].inverted);
  }

  // init wifi
  EEPROM.begin(EEPROM_SIZE);
  for (uint8_t i = 0; i < WIFI_SSID_LEN; i++) {
    wifi_ssid[i] = EEPROM.read(WIFI_SSID_ADDRESS + i);
  }
  for (uint8_t i = 0; i < WIFI_PASSWORD_LEN; i++) {
    wifi_password[i] = EEPROM.read(WIFI_PASSWORD_ADDRESS + i);
  }
  connect_to_wifi();
  MDNS.begin(HOSTNAME);

  //init plant config
  for (uint8_t i = 0; i < AMOUNT_OF_PLANTS; i++) {
    uint8_t len = sizeof(plant_config);
    uint8_t buf[len];
    EEPROM.readBytes(PLANTS_ADDRESS + i * len, &(plants[i].config), len);
  }
}

void loop() {
  static uint32_t last_measurement;
  // start server
  if (!server_active && (WiFi.isConnected() || hotspot_active)) {
    server.begin(80);
    server_active = true;
  }
  
  // update wifi status
  if (!WiFi.isConnected() && !hotspot_active) {
    //Serial.println("not connectd");
    //Serial.println(wifi_ssid);
    //Serial.println(wifi_password);
    connect_to_wifi();
  }

  // handle hotspot
  if (digitalRead(INIT_AP_PIN) == 0 && !hotspot_active) {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(HOTSPOT_SSID, HOTSPOT_PASSWORD);
    hotspot_active = true;
    Serial.println("enter hotspot");
  }

  updateServer();

  if (millis() - last_measurement < UPDATE_DELAY) {
    return;
  }
  last_measurement = millis();
  for (uint8_t i = 0; i < AMOUNT_OF_PLANTS; i++) {
    update_plant(&(plants[i]));
    updateServer();
  }
}
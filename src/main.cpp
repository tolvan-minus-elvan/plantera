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

#define HUMIDITY_SENSOR_MIN 14000
#define HUMIDITY_SENSOR_MAX 22000

#define PUMP_TIME 30000

#define WATER_LEVEL_MIN 0
#define WATER_LEVEL_MAX 20000

#define INIT_AP_PIN 4

#define WATER_LEVEL_MEASURE_PIN -1
#define WATER_LEVEL_CONTROL_PIN -1

#define LED_R_PIN -1
#define LED_G_PIN -1
#define LED_B_PIN -1
#define LED_R_CHANNEL 0
#define LED_G_CHANNEL 1
#define LED_B_CHANNEL 2

#define AMOUNT_OF_PLANTS 3

#define UPDATE_DELAY 1000 * 60 * 5 // every 5 minutes

struct plant_config {
  double lower_limit;
  double upper_limit;
};

struct plant_base {
  uint8_t sensor_measure_pin;
  uint8_t pump_control_pin;
  uint8_t is_connected_pin; 
  bool currently_watering = false;;
  plant_config config;
};

char wifi_password[WIFI_PASSWORD_LEN];
char wifi_ssid[WIFI_SSID_LEN];
bool hotspot_active = false;
bool server_active = false;
struct plant_base plants[AMOUNT_OF_PLANTS];
WiFiServer server;
WiFiClient client;

void dispRgb(uint8_t red, uint8_t green, uint8_t blue) {
  ledcWrite(LED_R_CHANNEL, red);
  ledcWrite(LED_G_CHANNEL, green);
  ledcWrite(LED_B_CHANNEL, blue);
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
    dispRgb(0, 0, 0); // no news are good news
  }
}

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
  if (msg.get_id() >= AMOUNT_OF_PLANTS) return; // wtf

  plant_base* target = &plants[msg.get_id()];
  target->config.lower_limit = msg.get_lower_limit();
  target->config.upper_limit = msg.get_upper_limit();
  EEPROM.writeBytes(PLANTS_ADDRESS + sizeof(plant_config) * msg.get_id(), &(target->config), sizeof(plant_config));
  EEPROM.commit();
  answerPost(nullptr, 0);
}

float read_water_level() {
  
}

void update_plant(plant_base plant) {
  if (!digitalRead(plant.is_connected_pin)) return;

  uint32_t raw_measurement = analogRead(plant.sensor_measure_pin);
  float humidity = (raw_measurement - HUMIDITY_SENSOR_MIN) / (HUMIDITY_SENSOR_MAX - HUMIDITY_SENSOR_MIN) * 100.0;

  if (humidity < plant.config.lower_limit) {
    plant.currently_watering = true;
  }

  if (humidity > plant.config.lower_limit) {
    digitalWrite(plant.pump_control_pin, LOW);
    plant.currently_watering = false;
  }

  if (plant.currently_watering) {
    digitalWrite(plant.pump_control_pin, HIGH);
    delay(PUMP_TIME);
    digitalWrite(plant.pump_control_pin, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  //init pins;
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(INIT_AP_PIN, INPUT_PULLDOWN);
  for (uint8_t i = 0; i < AMOUNT_OF_PLANTS; i++) {
    pinMode(plants[i].sensor_measure_pin, INPUT);
    pinMode(plants[i].is_connected_pin, INPUT_PULLDOWN);
    pinMode(plants[i].pump_control_pin, OUTPUT);
  }
  ledcSetup(LED_R_CHANNEL, 5000, 8);
  ledcSetup(LED_G_CHANNEL, 5000, 8);
  ledcSetup(LED_B_CHANNEL, 5000, 8);
  ledcAttachPin(LED_R_PIN, LED_R_CHANNEL);
  ledcAttachPin(LED_G_PIN, LED_G_CHANNEL);
  ledcAttachPin(LED_B_PIN, LED_B_CHANNEL);
  
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
    for (uint8_t j = 0; j < len; j++) {
      buf[i] = EEPROM.read(PLANTS_ADDRESS + j);
    }
    memcpy(&(plants[i].config), buf, len);
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
    dispRgb(255, 0, 0); // red
    connect_to_wifi();
  }
  read_water_level();

  // handle hotspot
  if (digitalRead(INIT_AP_PIN) && !hotspot_active) {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(HOTSPOT_SSID, HOTSPOT_PASSWORD);
    hotspot_active = true;
    dispRgb(255, 255, 0); // yellow
  }

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
        answerGet((uint8_t*) setup_page, sizeof(setup_page));
      } else {
        answerGet((uint8_t*) main_page, sizeof(main_page));
      }
    } else
    if (memcmp(first_line, "POST", 4) == 0) {
      prot::parse_message(line[0], line + 1);
    }
  }
  client.stop();

  if (millis() - last_measurement < UPDATE_DELAY) {
    return;
  }

  last_measurement = millis();
  for (uint8_t i = 0; i < AMOUNT_OF_PLANTS; i++) {
    update_plant(plants[i]);
  }
}
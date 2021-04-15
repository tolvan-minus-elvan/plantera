/*****************************
GENERATED FILE DO NOT EDIT
******************************/

#include <math.h>
#include <stdint.h>
#include <string.h>

namespace prot {
enum struct units : uint8_t {
  web = 0,
  plant = 1,
};
enum struct fields : uint8_t {
  SSID = 0,
  password = 1,
  plant_id = 2,
  humidity = 3,
  lower_limit = 4,
  upper_limit = 5,
};
enum struct messages : uint8_t {
  wifi_config = 0,
  get_active_plants = 1,
  get_humidity_measurement = 2,
  active_plants = 3,
  humidity_measurement = 4,
  configure_plant = 5,
};
template <typename T>
void scaledFloat_to_uint(double value, double scale, T *out) {
  *out = value * scale;
}

template <typename T>
void uint_to_scaledFloat(T value, double scale, double *out) {
  *out = value / scale;
}

template <typename T>
void packedFloat_to_uint(double value, double min, double max, T *out) {
  T max_value = ~0;
  double difference = max - min;
  *out = (value - min) / difference * max_value;
}

template <typename T>
void uint_to_packedFloat(T value, double min, double max, double *out) {
  T max_value = ~0;
  double difference = max - min;
  *out = difference * value / max_value;
}

class wifi_config_from_web_to_plant {
public:
  char SSID[64];
  static_assert((sizeof(SSID) == 64), "invalid size");
  char password[64];
  static_assert((sizeof(password) == 64), "invalid size");
  uint8_t size = 128;
  enum messages message = messages::wifi_config;
  enum units source = units::web;
  enum units target = units::plant;
  uint8_t get_size() { return size; }
  enum units get_source() { return source; }
  enum units get_target() { return target; }
  uint8_t id = 1;
  uint8_t get_id() { return id; }
  void set_SSID(char *value) { memcpy(SSID, value, sizeof(*SSID)); }
  void set_password(char *value) { memcpy(password, value, sizeof(*password)); }
  char *get_SSID() { return SSID; }
  char *get_password() { return password; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &SSID, sizeof(SSID));
    *index += sizeof(SSID);
    memcpy(buf + *index, &password, sizeof(password));
    *index += sizeof(password);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&SSID, buf + index, sizeof(SSID));
    index += sizeof(SSID);
    memcpy(&password, buf + index, sizeof(password));
    index += sizeof(password);
  }
};

class get_active_plants_from_web_to_plant {
public:
  uint8_t size = 0;
  enum messages message = messages::get_active_plants;
  enum units source = units::web;
  enum units target = units::plant;
  uint8_t get_size() { return size; }
  enum units get_source() { return source; }
  enum units get_target() { return target; }
  uint8_t id = 2;
  uint8_t get_id() { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) {}
  void parse_buf(uint8_t *buf) {}
};

class get_humidity_measurement_from_web_to_plant {
public:
  uint8_t size = 0;
  enum messages message = messages::get_humidity_measurement;
  enum units source = units::web;
  enum units target = units::plant;
  uint8_t get_size() { return size; }
  enum units get_source() { return source; }
  enum units get_target() { return target; }
  uint8_t id = 3;
  uint8_t get_id() { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) {}
  void parse_buf(uint8_t *buf) {}
};

class active_plants_from_plant_to_web {
public:
  uint8_t size = 0;
  enum messages message = messages::active_plants;
  enum units source = units::plant;
  enum units target = units::web;
  uint8_t get_size() { return size; }
  enum units get_source() { return source; }
  enum units get_target() { return target; }
  uint8_t id = 4;
  uint8_t get_id() { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) {}
  void parse_buf(uint8_t *buf) {}
};

class humidity_measurement_from_plant_to_web {
public:
  uint8_t plant_id;
  static_assert((sizeof(plant_id) == 1), "invalid size");
  double_t humidity;
  static_assert((sizeof(humidity) == 8), "invalid size");
  uint8_t size = 9;
  enum messages message = messages::humidity_measurement;
  enum units source = units::plant;
  enum units target = units::web;
  uint8_t get_size() { return size; }
  enum units get_source() { return source; }
  enum units get_target() { return target; }
  uint8_t id = 5;
  uint8_t get_id() { return id; }
  void set_plant_id(uint8_t value) { plant_id = value; }
  void set_humidity(double_t value) { humidity = value; }
  uint8_t get_plant_id() { return plant_id; }
  double_t get_humidity() { return humidity; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &plant_id, sizeof(plant_id));
    *index += sizeof(plant_id);
    memcpy(buf + *index, &humidity, sizeof(humidity));
    *index += sizeof(humidity);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&plant_id, buf + index, sizeof(plant_id));
    index += sizeof(plant_id);
    memcpy(&humidity, buf + index, sizeof(humidity));
    index += sizeof(humidity);
  }
};

class configure_plant_from_web_to_plant {
public:
  uint8_t plant_id;
  static_assert((sizeof(plant_id) == 1), "invalid size");
  double_t lower_limit;
  static_assert((sizeof(lower_limit) == 8), "invalid size");
  double_t upper_limit;
  static_assert((sizeof(upper_limit) == 8), "invalid size");
  uint8_t size = 17;
  enum messages message = messages::configure_plant;
  enum units source = units::web;
  enum units target = units::plant;
  uint8_t get_size() { return size; }
  enum units get_source() { return source; }
  enum units get_target() { return target; }
  uint8_t id = 6;
  uint8_t get_id() { return id; }
  void set_plant_id(uint8_t value) { plant_id = value; }
  void set_lower_limit(double_t value) { lower_limit = value; }
  void set_upper_limit(double_t value) { upper_limit = value; }
  uint8_t get_plant_id() { return plant_id; }
  double_t get_lower_limit() { return lower_limit; }
  double_t get_upper_limit() { return upper_limit; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &plant_id, sizeof(plant_id));
    *index += sizeof(plant_id);
    memcpy(buf + *index, &lower_limit, sizeof(lower_limit));
    *index += sizeof(lower_limit);
    memcpy(buf + *index, &upper_limit, sizeof(upper_limit));
    *index += sizeof(upper_limit);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&plant_id, buf + index, sizeof(plant_id));
    index += sizeof(plant_id);
    memcpy(&lower_limit, buf + index, sizeof(lower_limit));
    index += sizeof(lower_limit);
    memcpy(&upper_limit, buf + index, sizeof(upper_limit));
    index += sizeof(upper_limit);
  }
};

void rx(wifi_config_from_web_to_plant msg);
void rx(get_active_plants_from_web_to_plant msg);
void rx(get_humidity_measurement_from_web_to_plant msg);
void rx(active_plants_from_plant_to_web msg);
void rx(humidity_measurement_from_plant_to_web msg);
void rx(configure_plant_from_web_to_plant msg);
void parse_message(uint8_t id, uint8_t *buf);
bool is_valid_id(uint8_t id);
uint8_t id_to_len(uint8_t id);
enum units id_to_source(uint8_t id);
enum units id_to_target(uint8_t id);
} // namespace prot
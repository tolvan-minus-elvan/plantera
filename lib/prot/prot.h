/*****************************
GENERATED FILE DO NOT EDIT
******************************/

// pick if you want to use floats or doubles
#define prot_FLOAT_DEF float

#include <math.h>
#include <stdint.h>
#include <string.h>

namespace prot {
enum struct nodes : uint8_t {
  web = 0,
  plant = 1,
};
enum struct fields : uint8_t {
  SSID = 0,
  password = 1,
  plant_id = 2,
  lower_limit = 3,
  upper_limit = 4,
  water_level = 5,
  plant_0 = 6,
  plant_1 = 7,
  plant_2 = 8,
  plant_3 = 9,
  plant_4 = 10,
  plant_5 = 11,
  plant_6 = 12,
  plant_7 = 13,
  humidity = 14,
};
enum struct messages : uint8_t {
  wifi_config = 0,
  configure_plant = 1,
  get_connected_plants = 2,
  get_humidity_measurement = 3,
  get_configuration = 4,
  get_water_level = 5,
  water_level = 6,
  connected_plants = 7,
  humidity_measurement = 8,
  configuration = 9,
};
enum struct categories : uint8_t {
  none = 0,
};
template <typename T>
void scaledFloat_to_uint(prot_FLOAT_DEF value, prot_FLOAT_DEF scale, T *out) {
  *out = value * scale;
}

template <typename T>
void uint_to_scaledFloat(T value, prot_FLOAT_DEF scale, prot_FLOAT_DEF *out) {
  *out = value / scale;
}

template <typename T>
void packedFloat_to_uint(prot_FLOAT_DEF value, prot_FLOAT_DEF minValue,
                         prot_FLOAT_DEF maxValue, T *out) {
  T intMax = ~0;
  if (value < minValue) {
    *out = 0;
    return;
  }
  if (value > maxValue) {
    *out = intMax;
    return;
  }
  prot_FLOAT_DEF ratio = (value - minValue) / (maxValue - minValue);
  *out = 1 + ((intMax - 2)) * ratio;
}

template <typename T>
void uint_to_packedFloat(T value, prot_FLOAT_DEF minValue,
                         prot_FLOAT_DEF maxValue, prot_FLOAT_DEF *out) {
  T intMax = ~0;
  if (value <= 0) {
    *out = minValue - 1.0;
    return;
  }
  if (value >= intMax) {
    *out = maxValue + 1.0;
    return;
  }
  prot_FLOAT_DEF ratio = (value - 1) / (intMax - 2);
  *out = ratio * (maxValue - minValue) + minValue;
}

class wifi_config_from_web_to_plant {
public:
  char SSID[64];
  static_assert((sizeof(SSID) == 64), "invalid size");
  char password[64];
  static_assert((sizeof(password) == 64), "invalid size");
  uint8_t size = 128;
  enum messages message = messages::wifi_config;
  enum nodes sender = nodes::web;
  enum nodes receiver = nodes::plant;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 0;
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
  enum nodes sender = nodes::web;
  enum nodes receiver = nodes::plant;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 1;
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

class get_connected_plants_from_web_to_plant {
public:
  uint8_t size = 0;
  enum messages message = messages::get_connected_plants;
  enum nodes sender = nodes::web;
  enum nodes receiver = nodes::plant;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 2;
  uint8_t get_id() { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) {}
  void parse_buf(uint8_t *buf) {}
};

class get_humidity_measurement_from_web_to_plant {
public:
  uint8_t plant_id;
  static_assert((sizeof(plant_id) == 1), "invalid size");
  uint8_t size = 1;
  enum messages message = messages::get_humidity_measurement;
  enum nodes sender = nodes::web;
  enum nodes receiver = nodes::plant;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 3;
  uint8_t get_id() { return id; }
  void set_plant_id(uint8_t value) { plant_id = value; }
  uint8_t get_plant_id() { return plant_id; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &plant_id, sizeof(plant_id));
    *index += sizeof(plant_id);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&plant_id, buf + index, sizeof(plant_id));
    index += sizeof(plant_id);
  }
};

class get_configuration_from_web_to_plant {
public:
  uint8_t plant_id;
  static_assert((sizeof(plant_id) == 1), "invalid size");
  uint8_t size = 1;
  enum messages message = messages::get_configuration;
  enum nodes sender = nodes::web;
  enum nodes receiver = nodes::plant;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 4;
  uint8_t get_id() { return id; }
  void set_plant_id(uint8_t value) { plant_id = value; }
  uint8_t get_plant_id() { return plant_id; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &plant_id, sizeof(plant_id));
    *index += sizeof(plant_id);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&plant_id, buf + index, sizeof(plant_id));
    index += sizeof(plant_id);
  }
};

class get_water_level_from_web_to_plant {
public:
  uint8_t size = 0;
  enum messages message = messages::get_water_level;
  enum nodes sender = nodes::web;
  enum nodes receiver = nodes::plant;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 5;
  uint8_t get_id() { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) {}
  void parse_buf(uint8_t *buf) {}
};

class water_level_from_plant_to_web {
public:
  float_t water_level;
  static_assert((sizeof(water_level) == 4), "invalid size");
  uint8_t size = 4;
  enum messages message = messages::water_level;
  enum nodes sender = nodes::plant;
  enum nodes receiver = nodes::web;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 6;
  uint8_t get_id() { return id; }
  void set_water_level(float_t value) { water_level = value; }
  float_t get_water_level() { return water_level; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &water_level, sizeof(water_level));
    *index += sizeof(water_level);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&water_level, buf + index, sizeof(water_level));
    index += sizeof(water_level);
  }
};

class connected_plants_from_plant_to_web {
public:
  uint8_t bit_field = 0;
  static_assert((sizeof(bit_field) == 1), "invalid size");
  void set_plant_0(bool value) {
    bit_field =
        value * (bit_field | (1 << 0)) + !value * (bit_field & ~(1 << 0));
  }
  bool get_plant_0() { return bit_field & (1 << 0); }
  void set_plant_1(bool value) {
    bit_field =
        value * (bit_field | (1 << 1)) + !value * (bit_field & ~(1 << 1));
  }
  bool get_plant_1() { return bit_field & (1 << 1); }
  void set_plant_2(bool value) {
    bit_field =
        value * (bit_field | (1 << 2)) + !value * (bit_field & ~(1 << 2));
  }
  bool get_plant_2() { return bit_field & (1 << 2); }
  void set_plant_3(bool value) {
    bit_field =
        value * (bit_field | (1 << 3)) + !value * (bit_field & ~(1 << 3));
  }
  bool get_plant_3() { return bit_field & (1 << 3); }
  void set_plant_4(bool value) {
    bit_field =
        value * (bit_field | (1 << 4)) + !value * (bit_field & ~(1 << 4));
  }
  bool get_plant_4() { return bit_field & (1 << 4); }
  void set_plant_5(bool value) {
    bit_field =
        value * (bit_field | (1 << 5)) + !value * (bit_field & ~(1 << 5));
  }
  bool get_plant_5() { return bit_field & (1 << 5); }
  void set_plant_6(bool value) {
    bit_field =
        value * (bit_field | (1 << 6)) + !value * (bit_field & ~(1 << 6));
  }
  bool get_plant_6() { return bit_field & (1 << 6); }
  void set_plant_7(bool value) {
    bit_field =
        value * (bit_field | (1 << 7)) + !value * (bit_field & ~(1 << 7));
  }
  bool get_plant_7() { return bit_field & (1 << 7); }
  uint8_t size = 1;
  enum messages message = messages::connected_plants;
  enum nodes sender = nodes::plant;
  enum nodes receiver = nodes::web;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 7;
  uint8_t get_id() { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &bit_field, sizeof(bit_field));
    *index += sizeof(bit_field);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&bit_field, buf + index, sizeof(bit_field));
    index += sizeof(bit_field);
  }
};

class humidity_measurement_from_plant_to_web {
public:
  uint8_t plant_id;
  static_assert((sizeof(plant_id) == 1), "invalid size");
  double_t humidity;
  static_assert((sizeof(humidity) == 8), "invalid size");
  uint8_t size = 9;
  enum messages message = messages::humidity_measurement;
  enum nodes sender = nodes::plant;
  enum nodes receiver = nodes::web;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 8;
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

class configuration_from_plant_to_web {
public:
  uint8_t size = 0;
  enum messages message = messages::configuration;
  enum nodes sender = nodes::plant;
  enum nodes receiver = nodes::web;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 9;
  uint8_t get_id() { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) {}
  void parse_buf(uint8_t *buf) {}
};

void rx(wifi_config_from_web_to_plant msg);
void rx(configure_plant_from_web_to_plant msg);
void rx(get_connected_plants_from_web_to_plant msg);
void rx(get_humidity_measurement_from_web_to_plant msg);
void rx(get_configuration_from_web_to_plant msg);
void rx(get_water_level_from_web_to_plant msg);
void rx(water_level_from_plant_to_web msg);
void rx(connected_plants_from_plant_to_web msg);
void rx(humidity_measurement_from_plant_to_web msg);
void rx(configuration_from_plant_to_web msg);
void parse_message(uint8_t id, uint8_t *buf);
bool is_valid_id(uint8_t id);
uint8_t id_to_len(uint8_t id);
enum nodes id_to_sender(uint8_t id);
enum nodes id_to_receiver(uint8_t id);
enum categories id_to_category(uint8_t id);
} // namespace prot
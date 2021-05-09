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
  humidity = 6,
  is_connected = 7,
};
enum struct messages : uint8_t {
  wifi_config = 0,
  configure_plant = 1,
  get_water_level = 2,
  water_level = 3,
  get_plant_info = 4,
  plant_info = 5,
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
  float_t lower_limit;
  static_assert((sizeof(lower_limit) == 4), "invalid size");
  float_t upper_limit;
  static_assert((sizeof(upper_limit) == 4), "invalid size");
  uint8_t size = 9;
  enum messages message = messages::configure_plant;
  enum nodes sender = nodes::web;
  enum nodes receiver = nodes::plant;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 1;
  uint8_t get_id() { return id; }
  void set_plant_id(uint8_t value) { plant_id = value; }
  void set_lower_limit(float_t value) { lower_limit = value; }
  void set_upper_limit(float_t value) { upper_limit = value; }
  uint8_t get_plant_id() { return plant_id; }
  float_t get_lower_limit() { return lower_limit; }
  float_t get_upper_limit() { return upper_limit; }
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

class get_water_level_from_web_to_plant {
public:
  uint8_t size = 0;
  enum messages message = messages::get_water_level;
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
  uint8_t id = 3;
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

class get_plant_info_from_web_to_plant {
public:
  uint8_t plant_id;
  static_assert((sizeof(plant_id) == 1), "invalid size");
  uint8_t size = 1;
  enum messages message = messages::get_plant_info;
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

class plant_info_from_plant_to_web {
public:
  uint8_t plant_id;
  static_assert((sizeof(plant_id) == 1), "invalid size");
  float_t lower_limit;
  static_assert((sizeof(lower_limit) == 4), "invalid size");
  float_t upper_limit;
  static_assert((sizeof(upper_limit) == 4), "invalid size");
  float_t humidity;
  static_assert((sizeof(humidity) == 4), "invalid size");
  uint8_t bit_field = 0;
  static_assert((sizeof(bit_field) == 1), "invalid size");
  void set_is_connected(bool value) {
    bit_field =
        value * (bit_field | (1 << 0)) + !value * (bit_field & ~(1 << 0));
  }
  bool get_is_connected() { return bit_field & (1 << 0); }
  uint8_t size = 14;
  enum messages message = messages::plant_info;
  enum nodes sender = nodes::plant;
  enum nodes receiver = nodes::web;
  uint8_t get_size() { return size; }
  enum nodes get_sender() { return sender; }
  enum nodes get_receiver() { return receiver; }
  uint8_t id = 5;
  uint8_t get_id() { return id; }
  void set_plant_id(uint8_t value) { plant_id = value; }
  void set_lower_limit(float_t value) { lower_limit = value; }
  void set_upper_limit(float_t value) { upper_limit = value; }
  void set_humidity(float_t value) { humidity = value; }
  uint8_t get_plant_id() { return plant_id; }
  float_t get_lower_limit() { return lower_limit; }
  float_t get_upper_limit() { return upper_limit; }
  float_t get_humidity() { return humidity; }
  void build_buf(uint8_t *buf, uint8_t *index) {
    memcpy(buf + *index, &bit_field, sizeof(bit_field));
    *index += sizeof(bit_field);
    memcpy(buf + *index, &plant_id, sizeof(plant_id));
    *index += sizeof(plant_id);
    memcpy(buf + *index, &lower_limit, sizeof(lower_limit));
    *index += sizeof(lower_limit);
    memcpy(buf + *index, &upper_limit, sizeof(upper_limit));
    *index += sizeof(upper_limit);
    memcpy(buf + *index, &humidity, sizeof(humidity));
    *index += sizeof(humidity);
  }
  void parse_buf(uint8_t *buf) {
    uint8_t index = 0;
    memcpy(&bit_field, buf + index, sizeof(bit_field));
    index += sizeof(bit_field);
    memcpy(&plant_id, buf + index, sizeof(plant_id));
    index += sizeof(plant_id);
    memcpy(&lower_limit, buf + index, sizeof(lower_limit));
    index += sizeof(lower_limit);
    memcpy(&upper_limit, buf + index, sizeof(upper_limit));
    index += sizeof(upper_limit);
    memcpy(&humidity, buf + index, sizeof(humidity));
    index += sizeof(humidity);
  }
};

void rx(wifi_config_from_web_to_plant msg);
void rx(wifi_config_from_web_to_plant msg, void *misc);
void rx(configure_plant_from_web_to_plant msg);
void rx(configure_plant_from_web_to_plant msg, void *misc);
void rx(get_water_level_from_web_to_plant msg);
void rx(get_water_level_from_web_to_plant msg, void *misc);
void rx(water_level_from_plant_to_web msg);
void rx(water_level_from_plant_to_web msg, void *misc);
void rx(get_plant_info_from_web_to_plant msg);
void rx(get_plant_info_from_web_to_plant msg, void *misc);
void rx(plant_info_from_plant_to_web msg);
void rx(plant_info_from_plant_to_web msg, void *misc);
void parse_message(uint8_t id, uint8_t *buf);
void parse_message(uint8_t id, uint8_t *buf, void *misc);
bool is_valid_id(uint8_t id);
uint8_t id_to_len(uint8_t id);
enum nodes id_to_sender(uint8_t id);
enum nodes id_to_receiver(uint8_t id);
enum categories id_to_category(uint8_t id);
} // namespace prot
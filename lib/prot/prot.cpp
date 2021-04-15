/*****************************
GENERATED FILE DO NOT EDIT
******************************/

#include "prot.h"
#include <stdint.h>

namespace prot {
__attribute__((weak)) void rx(wifi_config_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_active_plants_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_humidity_measurement_from_web_to_plant msg) {}
__attribute__((weak)) void rx(active_plants_from_plant_to_web msg) {}
__attribute__((weak)) void rx(humidity_measurement_from_plant_to_web msg) {}
__attribute__((weak)) void rx(configure_plant_from_web_to_plant msg) {}
void parse_message(uint8_t id, uint8_t *buf) {
  switch (id) {
  case 1: {
    wifi_config_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 2: {
    get_active_plants_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 3: {
    get_humidity_measurement_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 4: {
    active_plants_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 5: {
    humidity_measurement_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 6: {
    configure_plant_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  }
}

bool is_valid_id(uint8_t id) {
  switch (id) {
  case 1:
    return true;
    break;
  case 2:
    return true;
    break;
  case 3:
    return true;
    break;
  case 4:
    return true;
    break;
  case 5:
    return true;
    break;
  case 6:
    return true;
    break;
  default:
    return false;
  }
}

uint8_t id_to_len(uint8_t id) {
  switch (id) {
  case 1:
    return 128;
    break;
  case 2:
    return 0;
    break;
  case 3:
    return 0;
    break;
  case 4:
    return 1;
    break;
  case 5:
    return 9;
    break;
  case 6:
    return 17;
    break;
  default:
    return 0;
  }
}

enum units id_to_source(uint8_t id) {
  switch (id) {
  case 1:
    return units::web;
    break;
  case 2:
    return units::web;
    break;
  case 3:
    return units::web;
    break;
  case 4:
    return units::plant;
    break;
  case 5:
    return units::plant;
    break;
  case 6:
    return units::web;
    break;
  }
}

enum units id_to_target(uint8_t id) {
  switch (id) {
  case 1:
    return units::plant;
    break;
  case 2:
    return units::plant;
    break;
  case 3:
    return units::plant;
    break;
  case 4:
    return units::web;
    break;
  case 5:
    return units::web;
    break;
  case 6:
    return units::plant;
    break;
  }
}

} // namespace prot
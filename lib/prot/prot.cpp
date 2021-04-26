/*****************************
GENERATED FILE DO NOT EDIT
******************************/

#include "prot.h"
#include <stdint.h>

namespace prot {
__attribute__((weak)) void rx(wifi_config_from_web_to_plant msg) {}
__attribute__((weak)) void rx(configure_plant_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_connected_plants_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_humidity_measurement_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_configuration_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_water_level_from_web_to_plant msg) {}
__attribute__((weak)) void rx(water_level_from_plant_to_web msg) {}
__attribute__((weak)) void rx(connected_plants_from_plant_to_web msg) {}
__attribute__((weak)) void rx(humidity_measurement_from_plant_to_web msg) {}
__attribute__((weak)) void rx(configuration_from_plant_to_web msg) {}
void parse_message(uint8_t id, uint8_t *buf) {
  switch (id) {
  case 0: {
    wifi_config_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 1: {
    configure_plant_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 2: {
    get_connected_plants_from_web_to_plant __message;
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
    get_configuration_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 5: {
    get_water_level_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 6: {
    water_level_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 7: {
    connected_plants_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 8: {
    humidity_measurement_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 9: {
    configuration_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  }
}

bool is_valid_id(uint8_t id) {
  switch (id) {
  case 0:
    return true;
    break;
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
  case 7:
    return true;
    break;
  case 8:
    return true;
    break;
  case 9:
    return true;
    break;
  default:
    return false;
  }
}

uint8_t id_to_len(uint8_t id) {
  switch (id) {
  case 0:
    return 128;
    break;
  case 1:
    return 17;
    break;
  case 2:
    return 0;
    break;
  case 3:
    return 1;
    break;
  case 4:
    return 1;
    break;
  case 5:
    return 0;
    break;
  case 6:
    return 4;
    break;
  case 7:
    return 1;
    break;
  case 8:
    return 9;
    break;
  case 9:
    return 0;
    break;
  default:
    return 0;
  }
}

enum nodes id_to_sender(uint8_t id) {
  switch (id) {
  case 0:
    return nodes::web;
    break;
  case 1:
    return nodes::web;
    break;
  case 2:
    return nodes::web;
    break;
  case 3:
    return nodes::web;
    break;
  case 4:
    return nodes::web;
    break;
  case 5:
    return nodes::web;
    break;
  case 6:
    return nodes::plant;
    break;
  case 7:
    return nodes::plant;
    break;
  case 8:
    return nodes::plant;
    break;
  case 9:
    return nodes::plant;
    break;
  }
}

enum nodes id_to_receiver(uint8_t id) {
  switch (id) {
  case 0:
    return nodes::plant;
    break;
  case 1:
    return nodes::plant;
    break;
  case 2:
    return nodes::plant;
    break;
  case 3:
    return nodes::plant;
    break;
  case 4:
    return nodes::plant;
    break;
  case 5:
    return nodes::plant;
    break;
  case 6:
    return nodes::web;
    break;
  case 7:
    return nodes::web;
    break;
  case 8:
    return nodes::web;
    break;
  case 9:
    return nodes::web;
    break;
  }
}

enum categories id_to_category(uint8_t id) {
  switch (id) {
  case 0:
    return categories::none;
    break;
  case 1:
    return categories::none;
    break;
  case 2:
    return categories::none;
    break;
  case 3:
    return categories::none;
    break;
  case 4:
    return categories::none;
    break;
  case 5:
    return categories::none;
    break;
  case 6:
    return categories::none;
    break;
  case 7:
    return categories::none;
    break;
  case 8:
    return categories::none;
    break;
  case 9:
    return categories::none;
    break;
  }
}

} // namespace prot
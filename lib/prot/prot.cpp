/*****************************
GENERATED FILE DO NOT EDIT
******************************/

#include "prot.h"
#include <stdint.h>

namespace prot {
__attribute__((weak)) void rx(wifi_config_from_web_to_plant msg) {}
__attribute__((weak)) void rx(wifi_config_from_web_to_plant msg, void *misc) {}
__attribute__((weak)) void rx(configure_plant_from_web_to_plant msg) {}
__attribute__((weak)) void rx(configure_plant_from_web_to_plant msg,
                              void *misc) {}
__attribute__((weak)) void rx(get_water_level_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_water_level_from_web_to_plant msg,
                              void *misc) {}
__attribute__((weak)) void rx(water_level_from_plant_to_web msg) {}
__attribute__((weak)) void rx(water_level_from_plant_to_web msg, void *misc) {}
__attribute__((weak)) void rx(get_plant_info_from_web_to_plant msg) {}
__attribute__((weak)) void rx(get_plant_info_from_web_to_plant msg,
                              void *misc) {}
__attribute__((weak)) void rx(plant_info_from_plant_to_web msg) {}
__attribute__((weak)) void rx(plant_info_from_plant_to_web msg, void *misc) {}
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
    get_water_level_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 3: {
    water_level_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 4: {
    get_plant_info_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  case 5: {
    plant_info_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message);
    break;
  }
  }
}

void parse_message(uint8_t id, uint8_t *buf, void *misc) {
  switch (id) {
  case 0: {
    wifi_config_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message, misc);
    break;
  }
  case 1: {
    configure_plant_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message, misc);
    break;
  }
  case 2: {
    get_water_level_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message, misc);
    break;
  }
  case 3: {
    water_level_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message, misc);
    break;
  }
  case 4: {
    get_plant_info_from_web_to_plant __message;
    __message.parse_buf(buf);
    rx(__message, misc);
    break;
  }
  case 5: {
    plant_info_from_plant_to_web __message;
    __message.parse_buf(buf);
    rx(__message, misc);
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
    return 9;
    break;
  case 2:
    return 0;
    break;
  case 3:
    return 4;
    break;
  case 4:
    return 1;
    break;
  case 5:
    return 14;
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
    return nodes::plant;
    break;
  case 4:
    return nodes::web;
    break;
  case 5:
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
    return nodes::web;
    break;
  case 4:
    return nodes::plant;
    break;
  case 5:
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
  }
}

} // namespace prot
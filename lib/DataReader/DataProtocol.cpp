#include "DataProtocol.h"
#include "prot.h"

//Can only read messages defined by the flight controller protocol
void DataProtocol::parse_byte(uint8_t byte) {
  switch(state) {
    case START1:
      if (byte == INIT_FRAME_1) {
        state = START2;
      }
      break;

    case START2:
      if (byte == INIT_FRAME_2) {
        state = TYPE;
      } else {
        state = START1;
      }
      break;

    case TYPE:
      if (not prot::is_valid_id(byte)) {
        state = START1;
        break;
      }
      payload_length = prot::id_to_len(byte);
      payload_id = byte;
      state = PAYLOAD;
      payload_index = 0;
      break;

    case PAYLOAD:
      payload_buf[payload_index] = byte;
      payload_index++;
      break;
  }

  if (payload_index == payload_length && state == PAYLOAD) {
    state = START1;
    payload_index = 0;
    (*callback)(payload_id, payload_buf, payload_length);
  }
}

//can read all messages
void DataProtocol::parse_frame(uint8_t* buf, uint8_t len) {
  if (buf[0] != INIT_FRAME_1 || buf[1] != INIT_FRAME_2) {
    return;
  }
  uint8_t id = buf[2];
  if (prot::id_to_len(id) != len - 3) {
    return;
  }
  (*callback)(id, buf + 3, len);
}

//can read all messages
void DataProtocol::build_header(uint8_t id, uint8_t* buf, uint8_t* index) {
  *index = 0;
  buf[(*index)++] = INIT_FRAME_1;
  buf[(*index)++] = INIT_FRAME_2;
  buf[(*index)++] = id;
}
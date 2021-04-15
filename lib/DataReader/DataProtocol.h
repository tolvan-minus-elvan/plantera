#include <stdint.h>
#include <string.h>
#define INIT_FRAME_1 0x0A
#define INIT_FRAME_2 0x0D

#define HEADER_SIZE 3
#define PAYLOAD_BUF_LEN 32

enum receiver_state {
    START1,
    START2,
    TYPE,
    PAYLOAD,
};

class DataProtocol {
public:
  void set_callback(void (*func)(uint8_t id, uint8_t* buf, uint8_t len)){
    callback=func;
  }

  void parse_byte(uint8_t byte);
  void parse_frame(uint8_t* buf, uint8_t len);

  void build_header(uint8_t id, uint8_t* buf, uint8_t* index);
  template <typename T>
  void build_buf(T msg, uint8_t* buf, uint8_t* len) {
    *len = 0;
    buf[(*len)++] = INIT_FRAME_1;
    buf[(*len)++] = INIT_FRAME_2;
    buf[(*len)++] = msg.get_id();
    msg.build_buf(buf, len);
  }

private:
  void (*callback)(uint8_t id, uint8_t* buf, uint8_t len);
  enum receiver_state state = START1;
  uint8_t payload_length;
  uint8_t payload_buf[PAYLOAD_BUF_LEN];
  uint8_t payload_index;
  uint8_t payload_id;
};
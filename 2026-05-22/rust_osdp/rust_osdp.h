#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct OsdpMessage {
  uint8_t addr;
  uint16_t length;
  uint8_t ctrl;
  uint8_t sec_blk_len;
  uint8_t sec_blk_type;
  uint8_t cmnd;
  uint32_t mac;
} OsdpMessage;

typedef struct OsdpFuncHandler {
  struct OsdpMessage (*function)(const struct OsdpMessage*);
  uint8_t command_id;
} OsdpFuncHandler;

typedef struct OsdpEngine {
  uint8_t id;
  bool processing_multiframe;
  uint8_t last_sequence;
  const struct OsdpFuncHandler *handler_functions;
  uint8_t handler_functions_size;
  struct OsdpMessage (*nack_handler_function)(const struct OsdpMessage*);
} OsdpEngine;

bool process_payload(struct OsdpEngine context, const unsigned char *data, unsigned long size);

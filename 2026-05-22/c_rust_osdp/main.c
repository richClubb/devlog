#include <stdio.h>

#include "rust_osdp.h"

int test() {
    return 50;
}

bool another() {
    return false;
}

OsdpMessage poll_func(OsdpMessage* message) {
    printf("Poll func handler\n");
    return *message;
}

OsdpFuncHandler poll_func_handler = {
    .function = poll_func,
    .command_id = 0x60
};

OsdpMessage id_func(OsdpMessage* message) {
    printf("ID func handler\n");
    return *message;
}

OsdpFuncHandler id_func_handler = {
    .function = id_func,
    .command_id = 0x61
};

OsdpMessage nack_function_handler(OsdpMessage message) {
    printf("NACK command handler\n");
    return message; 
}

int main(int argc, char** argv) {

    OsdpEngine osdp_engine;

    OsdpFuncHandler* func_handlers = (OsdpFuncHandler*)calloc(2, sizeof(OsdpFuncHandler));

    func_handlers[0] = poll_func_handler;
    func_handlers[1] = id_func_handler;

    osdp_engine.handler_functions = func_handlers;
    osdp_engine.handler_functions_size = 2;
    osdp_engine.nack_handler_function = nack_function_handler;

    printf("Poll command handler test\n");
    uint8_t data_1[] = {0x53, 0x00, 0x07, 0x00, 0x00, 0x60, 0x00, 0x01};

    const uint8_t* data_1_ptr = &data_1[0];

    bool result = process_payload(osdp_engine, data_1_ptr, 7);
    printf("Result: '%s'\n", result ? "true" : "false");

    printf("\n");

    printf("ID command handler test\n");
    uint8_t data_2[] = {0x00, 0x53, 0x00, 0x07, 0x00, 0x00, 0x61, 0x00, 0x01};

    const uint8_t* data_2_ptr = &data_2[0];

    result = process_payload(osdp_engine, data_2_ptr, 7);
    printf("Result: '%s'\n", result ? "true" : "false");

    printf("\n");

    printf("unknown command handler test\n");
    uint8_t data_3[] = {0x00, 0x53, 0x00, 0x07, 0x00, 0x00, 0x63, 0x00, 0x01};

    const uint8_t* data_3_ptr = &data_3[0];

    result = process_payload(osdp_engine, data_3_ptr, 7);
    printf("Result: '%s'\n", result ? "true" : "false");

    printf("\n");

    printf("Invalid ID test\n");
    osdp_engine.id = 0x01;

    result = process_payload(osdp_engine, data_3_ptr, 7);
    printf("Result: '%s'\n", result ? "true" : "false");
}
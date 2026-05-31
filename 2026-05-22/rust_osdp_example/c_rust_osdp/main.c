#include <stdio.h>

#include <stdint.h>

#include "rust_osdp.h"

static uint16_t nCrcTblValid = 0; 

static uint16_t cCrcTable[256];

static int fCrcTblInit( uint16_t *pTbl ) 
{ 
    int ii, jj; 
    uint16_t ww; 

    for (ii = 0; ii < 256; ii++) { 
        ww = (uint16_t)(ii << 8); 
        for (jj = 0; jj < 8; jj++) { 
            if ( ww & 0x8000 ) { 
                ww = (ww << 1) ^ 0x1021; 
            } else { 
                ww = (ww << 1); 
            } 
        } 
        pTbl[ii] = ww; 
    } 
    return 1; 
} 

// table based CRC - this is the "direct table" mode - 
uint16_t fCrcBlk( uint8_t *pData, uint16_t nLength) 
{ 
    uint16_t nCrc; 
    int ii; 

    if ( nCrcTblValid == 0 ) { 
        nCrcTblValid = fCrcTblInit(&cCrcTable[0]); 
    } 
    for ( ii = 0, nCrc = 0x1D0F; ii < nLength; ii++ ) { 
        nCrc = (nCrc<<8) ^ cCrcTable[ ((nCrc>>8) ^ pData[ii]) & 0xFF]; 
    } 
    return nCrc; 
} 

int test() {
    return 50;
}

bool another() {
    return false;
}

OsdpMessage poll_func(OsdpMessage* message) {
    printf("Poll func handler\n");
    printf("Something: %d\n", message->length);
    OsdpMessage* result = (OsdpMessage*)calloc(1, sizeof(OsdpMessage));
    return *result;
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

    uint8_t chksum_data[] = {0x53, 0x00, 0x08, 0x00, 0x04, 0x60}; 
    uint16_t chksum_result = fCrcBlk(chksum_data, 6);

    printf("Result: %x\n", chksum_result);


    OsdpEngine osdp_engine;

    OsdpFuncHandler* func_handlers = (OsdpFuncHandler*)calloc(2, sizeof(OsdpFuncHandler));

    func_handlers[0] = poll_func_handler;
    func_handlers[1] = id_func_handler;

    osdp_engine.handler_functions = func_handlers;
    osdp_engine.handler_functions_size = 2;
    osdp_engine.nack_handler_function = nack_function_handler;

    printf("Poll command handler test\n");
    uint8_t data_1[] = {0x53, 0x00, 0x07, 0x00, 0x00, 0x60, 0x46};

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
#include "xmc1100.h"

void main(void);
void default_handler(void);

const void* vectors[] __attribute__((section(".vector_table"))) = {
    (void*)0x2000C000,
    main,
    default_handler,
};

void default_handler(void) {
    while(1) {
        ;
    }
}

void delay(uint32 count) {

    for(uint32 index = 0; index < count; index++) {
        ;
    }
}

void main(void) {

    while(1) {

        PORT0 |= 0x01;
        delay(1000000);
        PORT0 &= ~0x01;
        delay(1000000);
    }

}


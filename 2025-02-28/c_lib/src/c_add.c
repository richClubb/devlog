#include <stdint.h>
#include "c_add.h"

uint8_t add_uint8_t(uint8_t a, uint8_t b)
{
    // check for wrapping behaviour
    uint16_t temp = 0;

    temp = a + b;

    if (temp > UINT8_MAX)
    {
        return UINT8_MAX;
    }
    
    return a + b;
}

uint8_t subtract_uint8_t(uint8_t a, uint8_t b)
{
    // check for wrapping behaviour
    int16_t temp = 0;

    temp = a - b;

    if (temp < 0)
    {
        return UINT8_MAX;
    }
    
    return a + b;
}
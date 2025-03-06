#include <stdint.h>
#include "c_int_math.h"

uint8_t c_uint8_add(uint8_t a, uint8_t b)
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

uint8_t c_uint8_sub(uint8_t a, uint8_t b)
{
    // check for wrapping behaviour
    int16_t temp = 0;

    temp = a - b;

    if (temp < 0)
    {
        return 0;
    }
    
    return a - b;
}
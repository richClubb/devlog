#include <stdint.h>

#include "cpp_int_math.h"

/*
    non wrapping addition
*/
uint8_t cpp_uint8_add(uint8_t a, uint8_t b)
{
    if ((UINT8_MAX - a) < b) return UINT8_MAX;

    return a + b;
}

/*
    non wrapping subtraction
*/
uint8_t cpp_uint8_sub(uint8_t a, uint8_t b)
{
    if ((UINT8_MAX - a) > b) return 0;

    return a - b;
}

/*
    Wrapping functions for C
*/
uint8_t c_cpp_uint8_add(uint8_t a, uint8_t b)
{
    return cpp_uint8_add(a, b);
}

uint8_t c_cpp_uint8_sub(uint8_t a, uint8_t b)
{
    return cpp_uint8_sub(a, b);
}

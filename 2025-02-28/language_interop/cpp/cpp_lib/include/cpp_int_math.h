#ifndef _CPP_MATH_LIB_

#define _CPP_MATH_LIB_

#ifdef __cplusplus
    #define EXTERN extern "C"
#else
    #define EXTERN
#endif

#include <stdint.h>

EXTERN uint8_t c_cpp_uint8_add(uint8_t, uint8_t);
EXTERN uint8_t c_cpp_uint8_sub(uint8_t, uint8_t);

uint8_t cpp_uint8_add(uint8_t, uint8_t);
uint8_t cpp_uint8_sub(uint8_t, uint8_t);

#undef EXTERN

#endif
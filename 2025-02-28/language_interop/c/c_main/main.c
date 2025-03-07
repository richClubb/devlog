#include "stdint.h"
#include "stdio.h"

#include "c_int_math.h"
#include "cpp_int_math.h"

void main(void)
{
    uint8_t temp;

    printf("C Language Interop\n\n");

    // Using C
    temp = c_uint8_add(1, 2);
    printf("Add using C: %d\n", temp);

    // Using C++
    temp = c_cpp_uint8_add(1, 2);
    printf("add using C++: %d\n", temp);
    
    // Using C#
    printf("add using C#: NOT IMPLEMENTED\n");

    // Using Python
    printf("add using Python: NOT IMPLEMENTED\n");

    // Using Rust
    printf("add using Rust: NOT IMPLEMENTED\n");
    
}
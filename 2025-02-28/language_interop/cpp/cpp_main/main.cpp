#include "stdint.h"
#include "stdio.h"

#include "cpp_int_math.h"

// I don't like this very much but I think I can do better.
extern "C" uint8_t c_uint8_add(uint8_t, uint8_t);

int main(void)
{
    uint8_t temp;

    printf("C++ Language Interop\n\n");

    // Using C
    temp = c_uint8_add(1, 2);
    printf("Add using C: %d\n", temp);

    // Using C++
    temp = cpp_uint8_add(1,2);
    printf("Add using C++: %d\n", temp);
    
    // Using C#
    printf("Add using C#: NOT IMPLEMENTED\n");

    // Using Python
    printf("Add using Python: NOT IMPLEMENTED\n");

    // Using Rust
    printf("Add using Rust: NOT IMPLEMENTED\n");
    
    return 0;
}
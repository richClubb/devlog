#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "mem_safety.h"


int main(int argc, char** argv) {

    SAFE_MEM* data = mem_safety_create(4, 4*sizeof(uint8_t));
    memset(data->ptr, 1, 4 * sizeof(uint8_t));

    // handy way to access data
    uint8_t* value = (uint8_t*)(data->ptr);
    uint8_t* ptr = (uint8_t*)(data->ptr);

    printf("Data: %p %p\n", data, data->ptr);
    for(uint8_t index = 0; index < data->size; index++)
    {
        printf("  Data value: %d %p\n", value[index], &value[index]);  
    }
    
    printf("Ptr: %d %p\n", *ptr, ptr);

    mem_safety_free(&data);

    // will give a segfault
    // printf("Data after free %p %p\n", data, data->ptr);
    // printf("Ptr after free: %d %p\n", *ptr, ptr);
}
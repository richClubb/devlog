#ifndef __MEM_SAFETY_H__

#define __MEM_SAFETY_H__

#include <stdint.h>
#include <stddef.h>

typedef struct safe_mem_t {
    void* ptr;
    size_t raw_size;
    size_t size;
} SAFE_MEM;

SAFE_MEM* mem_safety_create(size_t size, size_t raw_size);
void mem_safety_free(SAFE_MEM** obj);

#endif
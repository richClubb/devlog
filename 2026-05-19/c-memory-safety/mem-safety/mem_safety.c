#include "mem_safety.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/mman.h>


/*
    Purpose: 
    Parameters:
        * size - size of the data in the ptr
        * raw_size - raw size of the data in the ptr, use (sizeof("type") * size)
    Returns: NULL if object couldn't be created
*/
SAFE_MEM* mem_safety_create(size_t size, size_t raw_size) {
    SAFE_MEM* obj = (SAFE_MEM*)calloc(1, sizeof(SAFE_MEM));
    if (!obj) {
        return NULL;
    }

    // lock the object
    mlock(obj, sizeof(SAFE_MEM));

    obj->ptr = calloc(raw_size, sizeof(uint8_t));
    if (!obj->ptr) {
        mem_safety_free(&obj);
        return NULL;
    }
    mlock(obj->ptr, raw_size);

    // fill in sizes
    obj->raw_size = raw_size;
    obj->size = size;
    
    return obj;
}

/*
    Purpose: Clears and frees the data
             Takes in a pointer to the object pointer
    Parameters:
        * **obj - A pointer to the object pointer. Typically use &obj to enter the data
*/
void mem_safety_free(SAFE_MEM** obj) {

    if (!obj) {
        return;
    }

    if (!(*obj)){
        return;
    }

    SAFE_MEM *ptr = *obj;
    if(ptr->ptr){
        memset(ptr->ptr, 0, ptr->raw_size);
        // data freed, unlock the data pointer
        munlock(ptr->ptr, ptr->raw_size);
        free(ptr->ptr);
    }

    memset(ptr, 0, sizeof(SAFE_MEM));
    munlock(*obj, sizeof(SAFE_MEM));
    free(*obj);

    *obj = NULL;
}
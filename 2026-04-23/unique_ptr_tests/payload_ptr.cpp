
#include "payload_ptr.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>


PayloadPtr::PayloadPtr(uint8_t* data_ptr, uint32_t size) {

    this->ptr = (uint8_t *)calloc(sizeof(uint8_t), size);
    memcpy(this->ptr, data_ptr, size * sizeof(uint8_t));
    this->size = size;
}

PayloadPtr::~PayloadPtr() {

    if (this->ptr != NULL)
    {
        memset(this->ptr, 0, sizeof(uint8_t) * this->size);
        free(this->ptr);
    }
    this->size = 0;
}

PayloadPtr* PayloadPtr::create(uint8_t* data_ptr, uint32_t size) {
    
    PayloadPtr* payload = new PayloadPtr();
    payload->ptr = (uint8_t *)calloc(sizeof(uint8_t), size);
    memcpy(payload->ptr, data_ptr, size * sizeof(uint8_t));
    payload->size = size;

    return payload;
}

PayloadPtr* PayloadPtr::clone() {
    
    PayloadPtr* payload = new PayloadPtr();
    payload->ptr = (uint8_t *)calloc(sizeof(uint8_t), size);
    memcpy(payload->ptr, this->ptr, size * sizeof(uint8_t));
    payload->size = size;

    return payload;
}
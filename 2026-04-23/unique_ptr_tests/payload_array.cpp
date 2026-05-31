#include "payload_array.h"
#include <cstring>


PayloadArray::PayloadArray(uint8_t* data, uint32_t size) {
    this->data = std::unique_ptr<uint8_t[]>(new uint8_t[size]);

    for(uint32_t index; index < size; index++){
        this->data[index] = data[index];
    }

}

PayloadArray::~PayloadArray() {

}

PayloadArray* PayloadArray::create(uint8_t* data, uint32_t size) {

    
    return NULL;
}
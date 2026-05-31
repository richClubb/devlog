
#include "payload_vector.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>

PayloadVector::~PayloadVector() {


}

PayloadVector* PayloadVector::create(uint8_t* data_ptr, uint32_t size) {
    
    PayloadVector* payload = new PayloadVector();

    return payload;
}

PayloadVector* PayloadVector::clone() {
    
    PayloadVector* payload = new PayloadVector();

    return payload;
}
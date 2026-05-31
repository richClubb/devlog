#ifndef __PAYLOAD_VECTOR_H__

#define __PAYLOAD_ARRAY_H__

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

class PayloadVector {
public:
    
    std::vector<uint8_t> data;
    uint32_t size;

    PayloadVector() = default;
    ~PayloadVector();
    
    static PayloadVector* create(uint8_t* data_ptr, uint32_t size);
    PayloadVector* clone();

};

#endif
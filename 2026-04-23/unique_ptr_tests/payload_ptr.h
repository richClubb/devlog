#ifndef __PAYLOAD_PTR_H__

#define __PAYLOAD_PTR_H__

#include <cstdint>
#include <cstdlib>
#include <cstring>

class PayloadPtr {
public:
    
    uint8_t* ptr;
    uint32_t size;

    PayloadPtr() = default;
    PayloadPtr(uint8_t* data_ptr, uint32_t size);
    ~PayloadPtr();
    
    static PayloadPtr* create(uint8_t* data_ptr, uint32_t size);
    PayloadPtr* clone();

};

#endif
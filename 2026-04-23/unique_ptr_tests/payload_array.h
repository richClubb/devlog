#ifndef __PAYLOAD_ARRAY_H__

#define __PAYLOAD_ARRAY_H__

#include <memory>

class PayloadArray {
public:
    std::unique_ptr<uint8_t[]> data;
    
    PayloadArray() = default;
    PayloadArray(uint8_t* data, uint32_t size);
    ~PayloadArray();

    static PayloadArray* create(uint8_t* data, uint32_t size);

};


#endif




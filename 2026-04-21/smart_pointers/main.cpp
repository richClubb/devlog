
#include <stdint.h>
#include <cstdlib>
#include <memory>

class OsdpPayload {
public:
    std::unique_ptr<uint8_t[]> ptr;
    uint32_t size;

    ~OsdpPayload();

    static OsdpPayload* create(uint8_t *ptr, uint32_t size);

    OsdpPayload* clone();
private:
    OsdpPayload() = default;


};

OsdpPayload::~OsdpPayload() {

}

OsdpPayload* OsdpPayload::create(uint8_t *ptr, uint32_t size)
{
    ptr = (uint8_t *)calloc(sizeof(uint8_t), size);
    if (!ptr) {
        return NULL;
    }

    this->unique_ptr(new uint8_t[size]);
    
    
    return NULL;
}

OsdpPayload* OsdpPayload::clone() {
    
    return OsdpPayload::create(NULL, 0);
}


int main(int argc, char **argv) {

    uint8_t *ptr = (uint8_t *)calloc(sizeof(uint8_t), 2);
    ptr[0] = 0;
    ptr[1] = 1;

    std::unique_ptr<uint8_t[]> smart_ptr(new uint8_t[2]);
    smart_ptr[0] = 2;
    smart_ptr[1] = 3;

    // std::unique_ptr<OsdpPayload> payload_1 = OsdpPayload::create()

    return 1;
}
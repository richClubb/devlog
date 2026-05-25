
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstddef>

#include <memory>

std::atomic<bool> stop_thread = false;

class PayloadPtr {

    uint8_t* ptr;
    uint32_t size;

public:
    PayloadPtr() = default;
    ~PayloadPtr();
    static PayloadPtr* create(uint8_t* ptr, uint32_t size);

};


PayloadPtr::~PayloadPtr() {
    
    memset(this->ptr, sizeof(uint8_t) * this->size, 0);
    if (this->ptr != NULL) {
        free(this->ptr);
    }
    this->size = 0;
}


PayloadPtr* PayloadPtr::create(uint8_t* data_ptr, uint32_t size)
{
    
    return new PayloadPtr();
}


void func_thread(){

    while(stop_thread == false) {
        
    }

}


int main(int argc, char** argv) {

    PayloadPtr* payload = PayloadPtr::create(NULL, 1);

    std::unique_ptr<int*> payload_2 = std::make_unique<int *>(new int(1));

    return 0;
}

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <memory>

#include "payload_ptr.h"
#include "payload_array.h"


int main(int argc, char** argv) {

    uint8_t* data_1 = (uint8_t *)calloc(sizeof(uint8_t), 4);
    memset(data_1, 0x5a, sizeof(uint8_t) * 4);

    uint8_t* data_2 = (uint8_t *)calloc(sizeof(uint8_t), 4);
    memset(data_2, 0xa5, sizeof(uint8_t) * 4);

    uint8_t* data_3 = (uint8_t *)calloc(sizeof(uint8_t), 4);
    memset(data_3, 0x90, sizeof(uint8_t) * 4);

    printf("Test\n");

    PayloadPtr* payload_ptr_1 = PayloadPtr::create(data_1, 4);
    printf("%d\n", *payload_ptr_1->ptr);
    delete payload_ptr_1;

    std::unique_ptr<PayloadPtr> payload_unique_1(new PayloadPtr(data_2, 4));
    printf("%d\n", *payload_unique_1->ptr);

    *payload_unique_1->ptr = 95;
    printf("%d\n", *payload_unique_1->ptr);

    std::unique_ptr<PayloadArray> payload_unique_array_1(new PayloadArray(data_3, 4));
    printf("%d\n", payload_unique_array_1->data[0]);

    free(data_1);
    free(data_2);
    free(data_3);

    return 0;
    
}
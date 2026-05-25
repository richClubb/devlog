#include <stdio.h>

#include <sodium.h>
#include <sodium/utils.h>

int main(int argc, char** argv) {

    printf("libsodium example\n");

    if (0 > sodium_init()) {
        return 2;
    }

    uint32_t* data = (uint32_t*)sodium_malloc(sizeof(uint32_t));
    if (!data) {
        printf("Data alloc failed\n");
        return 1;
    }

    *data = 5;

    printf("Data: %d, %p\n", *data, data);
  
    // sodium_mprotect_noaccess(data);
    printf("Data locked noaccess, if attempted to read it will segfault\n");
    // causes a segfault
    // printf("Data: %d, %p\n", *data, data);

    sodium_mprotect_readonly(data);
    printf("Data readonly: %d, %p\n", *data, data);

    // causes a segfault
    // *data = 6;

    sodium_mprotect_readwrite(data);
    printf("Data readwrite before change: %d, %p\n", *data, data);
    *data = 6;
    printf("Data readwrite after change: %d, %p\n", *data, data);

    sodium_free(data);

    return 0;
}
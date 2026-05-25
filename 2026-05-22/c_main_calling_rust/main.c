#include <stdio.h>

#include "my_header.h"

int test() {
    return 50;
}

bool another() {
    return false;
}


int main(int argc, char** argv) {

    ALibObject test_1 = init_lib();

    printf("C calling Rust example\n");

    printf("%p\n", &test_1);

    printf("test_1 a_thing_1 ptr: %p\n", test_1.a_thing_1);
    printf("test_1 a_thing_1 value: %ld\n", test_1.a_thing_1());
    printf("test_1 a_thing_2 ptr: %p\n", test_1.a_thing_2);
    printf("test_1 a_thing_1 value: %ld\n", test_1.a_thing_2());
    printf("test_1 check_func ptr: %p\n", test_1.check_func);
    printf("test_1 check_func value: %s\n", test_1.check_func() ? "true" : "false"); 

    printf("rust lib process ptr: %p\n", process);
    printf("rust lib process value: %d\n", process(test_1));

    printf("Setting test_1.a_things_1 to c function\n");
    test_1.a_thing_1 = test;
    printf("test_1 a_thing_1 new value: %d\n", test_1.a_thing_1());

    printf("Setting test_1.check_func to c function\n");
    test_1.check_func = another; 
    printf("rust lib process value %d\n", process(test_1));
}
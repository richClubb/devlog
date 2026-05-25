#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <functional>

class TestClass {
public:
    TestClass(int number) {
        this->number = number;
    };

    void callback() {
        printf("Number %d\n", this->number);
    }

private:
    int number;

};


typedef void (testFuncPtr)(void); 


void func_1() {
    printf("In func 1\n");
}


void func_2() {
    printf("In func 2\n");
}


typedef struct funcPointerPair_t {
    testFuncPtr *callback_func;
    uint8_t cmdCode;
} funcPointerPair_t;


funcPointerPair_t *callback_func_table;

int main(void){

    TestClass a_object = TestClass(15);

    callback_func_table = (funcPointerPair_t*)calloc(3, sizeof(funcPointerPair_t));
    callback_func_table[0] = {func_1, 0};
    callback_func_table[1] = {func_2, 1};

    for(uint32_t index = 0; index < 3; index++)
    {
        callback_func_table[index].callback_func();
    }

    

    return 0;
}
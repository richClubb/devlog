#include "stdint.h"
#include "stdio.h"

#include "c_add.h"

void main(void)
{
    uint8_t temp;

    temp = add_uint8_t(1, 2);

    printf("%d\n", temp);
    
}
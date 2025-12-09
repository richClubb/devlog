#include <stdio.h>
#include <stdint.h>


void main(int argc, char **argv)
{

    int array[4] = {1, 2, 3, 4};

    for(uint8_t index = 0; index < 5; index++)
    {
        printf("%d\n", array[index]);
    }

    return;
}
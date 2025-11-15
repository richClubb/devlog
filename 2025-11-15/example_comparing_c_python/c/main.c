#include <stdio.h>

int main(int argc, char** argv)
{

    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    {
        int total = 0;
        for (int index = 0; index < 10; index++)
        {
            total += array[index];
        }
        printf("Total (method 1) is: %d\n", total);
    }

    {
        int total = 0;
        for (int index = 0; index < 10; index++)
        {
            total = total + array[index];
        }
        printf("Total (method 2) is: %d\n", total);
    }

    {
        int index = 0;
        int total = 0;
        while(index < 10)
        {
            total += array[index];
            index++;
        }
        printf("Total (method 3) is: %d\n", total);
    }
}
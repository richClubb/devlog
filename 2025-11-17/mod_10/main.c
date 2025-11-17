#include <stdbool.h>
#include <stdio.h>

bool match_last_digit_recursive(int probe, int comp, int *pos)
{
    if (probe == 0) return false;

    if ((probe % 10) == comp) {
        return true;
    }

    *pos += 1;
    return match_last_digit_recursive(probe / 10, comp, pos);
}

bool match_last_digit_loop(int probe, int comp, int *pos)
{
    int temp_probe = probe;
    while(true)
    {
        if ((temp_probe % 10) == comp)
        {
            return true;
        }

        *pos += 1;
        temp_probe = temp_probe / 10;

        if (temp_probe == 0)
        {
            return false;
        }
    }
}


int main(int argc, char **argv)
{
    printf("Loop version\n");
    {
        int val = 1234;
        int comp = 1;
        int pos = 0;
        if (match_last_digit_loop(val, comp, &pos))
        { 
            printf("Found %d in %d in pos %d\n", comp, val, pos + 1);
        }
        else
        {
            printf("Didn't find %d in %d\n", comp, val);
        }
    }

    {
        int val = 1234;
        int comp = 5;
        int pos = 0;
        if (match_last_digit_loop(val, comp, &pos))
        { 
            printf("Found %d in %d in pos %d\n", comp, val, pos + 1);
        }
        else
        {
            printf("Didn't find %d in %d\n", comp, val);
        }
    }
    
    printf("Recursive version\n");
    {
        int val = 1234;
        int comp = 1;
        int pos = 0;
        if (match_last_digit_recursive(val, comp, &pos))
        { 
            printf("Found %d in %d in pos %d\n", comp, val, pos + 1);
        }
        else
        {
            printf("Didn't find %d in %d\n", comp, val);
        }
    }

    {
        int val = 1234;
        int comp = 5;
        int pos = 0;
        if (match_last_digit_recursive(val, comp, &pos))
        { 
            printf("Found %d in %d in pos %d\n", comp, val, pos + 1);
        }
        else
        {
            printf("Didn't find %d in %d\n", comp, val);
        }
    }

    return 0;
}
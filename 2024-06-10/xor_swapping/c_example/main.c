#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = 15;

	printf("Swapping example using XOR in C\n");
	printf("Initial -> a = %d, b = %d\n", a, b);
	
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	printf("After swapping -> a = %d, b = %d\n", a, b);
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 24

/*software base self test for the integer division*/

int main(int argc, char *argv[])
{
	int a[N] = {0x7777,0x5555, 0xAAAA,0xAAAA,0x5555,INT_MIN,INT_MAX,1024,1024,555,555,5,INT_MAX,INT_MIN,INT_MAX,INT_MIN,2, 1323, 234, 43, 545343, 1000,1 ,0};
	int b[N] = {0x1234,0xAAAA,0x5555,7456,798,465,1234,5,4,13,10,0,INT_MAX,INT_MIN,1,1,2, 1,13, 2, 4, 54, 10 ,1,5};
	volatile int c[N];
	int i;

	for(i=0; i<N; i++) {
		c[i] = a[i] / b[i];
	}
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int a[5] = { 1323, 234, 43, 545343, 1000 };
	int b[5] = { 13, 2, 4, 54, 10 };
	volatile int c[5];
	volatile int expected [5]= { 101 , 117,10 , 10098 ,10  }
	int i;

	for(i=0; i<5; i++) {
		c[i] = a[i] / b[i];
	}
	for(i=0;i<5;i++) {
	if( c[i]!= expected[i]) {
	return EXIT_FAILURE;
	}
	
	}

    /* inline assembly */
    //asm volatile("ecall");
    /* write something to stdout */
    //printf("hello mondo world!\n");
    return EXIT_SUCCESS;
}

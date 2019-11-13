#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int a[5] = { 1323, 234, 43, 545343, 1000 };
	int b[5] = { 13, 2, 4, 54, 10 };
	volatile int c[5];

	int i;

	/*Apply the SBST flow on the integer division unit of the RI5CY processor. 
	 * You can start modifying the “sbst_c” program, which already includes a basic loop the performs integer divisions.
	 * Remember that the results should be stored in the data memory in order to propagate the effect of the faults up to the data bus, 
	 * which is observed by TetraMAX during the fault simulation (in the example program, this is implemented by using the volatile keyword in the variable definitions).*/

	for(i=0; i<5; i++) {
		c[i] = a[i] / b[i];
	}


	/* inline assembly */
	//asm volatile("ecall");
	/* write something to stdout */
	//printf("hello mondo world!\n");
	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#define N_REGS 32  // for integer and for floating point operation 

/*The register file can be successfully tested by means of the March-C algorithm. 
 * In the following, the algorithm pseudo-code is reported:
 for each register REG do
 A  pattern
 Write A in REG
 Store REG in memory
 A  invert pattern
 Write A in REG
 Store REG in memory
 loop
 Try using the following values as possible patterns: 00000000, 0000FFFF, 00FF00FF, 0F0F0F0F, 33333333, 55555555. 
 Try also to use a different pattern for each register. */
	

int main(int argc, char *argv[])
{
	int pattern [6] = {0x00000000, 0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555};	
	int i;
	volatile int a;
	register int b asm ("1");
	volatile int c;	

/*testing integer register file */
	for ( i=0;i<N_REGS/5;i++) {
	a= pattern[0];	  
	b = a;
	c=a;
	
	a= !pattern[0];
	b=a;
	c=b;

	}
		
/*testing floating point register file */
	for( i=0;i<N_REGS;i++) {

	

	}

	return EXIT_SUCCESS;
}

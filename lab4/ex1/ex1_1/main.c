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

char regs[32][]= {"1","2","3","4","5","6","7","8","9","10",
	"11","12","13","14","15","16","17","18","19","20",
	"21","22","23","24","25","26","27","28","29","30",
	"31","32","0"};
int main(int argc, char *argv[])
{
	int pattern [6] = {0x00000000, 0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555};	
	int i;
	volatile int a;
	volatile int c;	

	/*testing integer register file with differetnt pattern for each register */
	for ( i=0;i<N_REGS/6;i+=6) {
		// pattern 1
		a= pattern[0];	  
		register int b asm (regs[i]);
		b = a;
		c=a;

		a= !pattern[0];
		b=a;
		c=b;
		//pattern 2
		a= pattern[1];	  
		register  b asm (regs[i+1]);
		b = a;
		c=a;

		a= !pattern[1];
		b=a;
		c=b;
		// pattern 3 
		a= pattern[2];	  
		register b asm (regs[i+2]);
		b = a;
		c=a;

		a= !pattern[2];
		b=a;
		c=b;

		// pattern 4
		a= pattern[3];	  
		register int b asm (regs[i+3]);
		b = a;
		c=a;

		a= !pattern[3];
		b=a;
		c=b;
		// pattern 5	
		a= pattern[4];	  
		register int b asm (regs[i+4]);
		b = a;
		c=a;

		a= !pattern[4];
		b=a;
		c=b;
		// pattern 6
		a= pattern[5];
		register int b asm (regs[i+5]);
		b=a;
		c=a;
		a=!pattern[4];
		b=a;
		c=b;
	}

	/*testing floating point register file */
	for( i=0;i<N_REGS;i++) {



	}

	return EXIT_SUCCESS;
}

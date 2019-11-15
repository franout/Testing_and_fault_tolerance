#include <stdio.h>
#include <stdlib.h>
#define N_REGS 31  // for integer and for floating point operation 

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



/* NOTE:  x stands for integer registers
 * 	f for floating point registers
 *
 * */
/*register x0 is read only */
char * regs[N_REGS]= {"x1","x2","x3","x4","x5","x6","x7","x8","x9","x10",
	"x11","x12","x13","x14","x15","x16","x17","x18","x19","x20",
	"x21","x22","x23","x24","x25","x26","x27","x28","x29","x30",
	"x31","x32"};

int main(int argc, char *argv[])
{
	int pattern [6] = {0x00000000, 0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555};	
	int i;
	volatile int a;
	volatile int c;	
	// hint to the compiler for putting the variable into a register (ATTENTION it will not force it ) 
	/*testing integer register file with differetnt pattern for each register */
	for ( i=0;i<N_REGS;i+=6) {
		// pattern 1
		register int d asm("%1"
						:  "m" (regs[i])
				);

		a= pattern[0];	  
		d=a;
		c=d;	

		a= !pattern[0];
		d=a;
		c=d; 
		//pattern 2
		register int e asm("x2");

		a= pattern[0];	  
		e=a;
		c=e;	

		a= !pattern[0];
		e=a;
		c=e; 


		//pattern 3 	
		register int f asm("x3");

		a= pattern[0];	  
		f=a;
		c=f;	

		a= !pattern[0];
		f=a;
		c=f; 


		//pattern 4
		register int g asm("x4");

		a= pattern[0];	  
		g=a;
		c=g;	

		a= !pattern[0];
		g=a;
		c=g; 


		//pattern 5
		register int h asm("x5");

		a= pattern[0];	  
		h=a;
		c=h;	

		a= !pattern[0];
		h=a;
		c=h; 

	}
	/*testing floating point register file */
	for( i=0;i<N_REGS;i++) {



	}

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#define N_PATT 10  // for integer and for floating point operation 

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

int main(int argc, char *argv[])
{
	int pattern [N_PATT] = {0xF0F0F0F0,0xAAAAAAAA,0x00000000, 0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555,0xFFFFFFFF,0xCAFFECAFFE};	
	int i;
	volatile int a;
	volatile int c;	
	// hint to the compiler for putting the variable into a register (ATTENTION it will not force it ) 
	/*testing integer register file with differetnt pattern for each register */
	for ( i=0;i<N_PATT;i++) {


		register int x ;
		a= pattern[i];	  
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		a=~pattern[i];	
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("sw %0,%1": "=r" (x) : "m" (c));
		a= pattern[i];	  
		asm volatile ("lb %0,%1": "=r" (x) : "m" (a));
		asm volatile ("sb %0,%1": "=r" (x)  :"m" (c));
		a=~pattern[i];
		asm volatile ("lb %0,%1": "=r" (x) : "m" (a));
		asm volatile ("sb %0,%1": "=r" (x) : "m" (c));


		// several reading at time
		a= pattern[i];	  
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		a=~pattern[i];	
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("lw %0,%1": "=r" (x) : "m" (a));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
		asm volatile ("sw %0,%1": "=r" (x)  :"m" (c));
	}

	// special operations 
	asm volatile ("auipc x0,%0":: "i" (0x00f) );
	asm volatile ("lui x0, %0" ::"i" (0x00f) );

	asm volatile ("auipc %0,%1": "=r" (x): "i" (0x00f) );
	c=x;
	asm volatile ("lui %0, %1" : "=r" (x) :"i" (0x00f) );
	c=x;

	return EXIT_SUCCESS;
}

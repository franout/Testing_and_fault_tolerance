#include <stdio.h>
#include <stdlib.h>

/*
 *
 Write VALUEA in REGA
 Write VALUEB in REGB
 ALU_OP (dest: REGC, op1: REGA, op2: REGB)
 Store REGC in memory
 ALU_OP (dest: REGC, op1: REGB, op2: REGA)
 Store REGC in memory
 *
 * */

/* NOTE:  x stands for integer registers
 * 	f for floating point registers
 *
 * */
/*register x0 is read only */

int main(int argc, char *argv[])
{
	int pattern [6] = {0x00000000, 0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555};	
	int i;
	volatile int res;

	/*testing integer ALU */

	for ( i=0;i<6-1;i++) {
		// addition 	
		register int a asm("x1")=pattern[i];
		register int b asm("x2")=pattern[i+1];
		register int c asm("x3")=a+b;
		res=c;
		c=b+a;
		res=c;
		// subtraction
		c=a-b; 
		res=c;
		c=b-a;
		res=c;


		//not
		c=~a; 
		res=c;
		c=~b;
		res=c;

		//and
		c=a&b; 
		res=c;
		c=b&a;
		res=c;

		//or
		c=a|b; 
		res=c;
		c=b|a;
		res=c;

		//xor
		c=a^b; 
		res=c;
		c=b^a;
		res=c;

		//shift left	
		c=a<<b; 
		res=c;
		c=b<<a;
		res=c;

		//shift right 
		c=a>>b; 
		res=c;
		c=b>>a;
		res=c;

		// integer mul 
		c=a*b; 
		res=c;
		c=b*a;
		res=c;





		// integer division
		c=a/b; 
		res=c;
		c=b/a;
		res=c;


		// integer module
		c=a%b; 
		res=c;
		c=b%a;
		res=c;

		// comparison 
		c=a>b;
		res=c;
		c=b>a;
		res=c;
		// comparison 
		c=a<b;
		res=c;
		c=b<a;
		res=c;
		// comparison 
		c=a==b;
		res=c;
		c=b==a;
		res=c;
	}
	for ( i=0;i<6-1;i++) {
		// addition 	
		register int a asm("x1")=~pattern[i];
		register int b asm("x2")=~pattern[i+1];
		register int c asm("x3")=a+b;
		res=c;
		c=b+a;
		res=c;
		// subtraction
		c=a-b; 
		res=c;
		c=b-a;
		res=c;


		//not
		c=~a; 
		res=c;
		c=~b;
		res=c;

		//and
		c=a&b; 
		res=c;
		c=b&a;
		res=c;

		//or
		c=a|b; 
		res=c;
		c=b|a;
		res=c;

		//xor
		c=a^b; 
		res=c;
		c=b^a;
		res=c;

		//shift left	
		c=a<<b; 
		res=c;
		c=b<<a;
		res=c;

		//shift right 
		c=a>>b; 
		res=c;
		c=b>>a;
		res=c;

		// integer mul 
		c=a*b; 
		res=c;
		c=b*a;
		res=c;





		// integer division
		c=a/b; 
		res=c;
		c=b/a;
		res=c;


		// integer module
		c=a%b; 
		res=c;
		c=b%a;
		res=c;

		// comparison 
		c=a>b;
		res=c;
		c=b>a;
		res=c;
		// comparison 
		c=a<b;
		res=c;
		c=b<a;
		res=c;
		// comparison 
		c=a==b;
		res=c;
		c=b==a;
		res=c;
	}

	return EXIT_SUCCESS;
}

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

		for ( i=0;i<6;i++) {
		// addition 	
		register  int a asm("x1")=pattern[i];
		register  int b asm("x2")=pattern[i];
		register  int c asm("x3");
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b+a;
		res=c;
		// immediate addition
		asm volatile("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0x3));
		res=c;


		// subtraction
		asm volatile ("sub  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile ("sub  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b-a;
		res=c;


		//and
		asm volatile ("and %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		//	c=a&b; 
		res=c;
		asm volatile("and %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//or
		asm("or %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("or %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//xor
		asm("xor %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("xor %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//shift left logic
		asm("sll %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("sll %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right logic 
		asm("srl %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("srl %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		//shift left arithmetic
		asm("slt %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("slt %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right arithmetic
		asm("sra %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("sra %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer mul 
		asm("mul %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("mul %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer division
			asm("div %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		// integer unsigned division 
			asm("divu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		// integer module
				asm("rem %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;

		// integer unsigned module
		asm("remu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;


		// nope
	asm("nop");	
		res=c;


		asm ("lui %0,%1": "=r" (c): "i" (0x000FF));
		res=c;
	

		asm ("auipc %0,%1": "=r" (c): "i" (0x000FF));
		res=c;
	
	// comparison 
		
		// comparison 
		// comparison 
	}
for ( i=0;i<6;i++) {
		// addition 	
		register  int a asm("x1")=~pattern[i];
		register  int b asm("x2")=~pattern[i];
		register  int c asm("x3");
		asm("add  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b+a;
		res=c;
		// immediate addition
		asm("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0x3));
		res=c;


		// subtraction
		asm("sub  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm("sub  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b-a;
		res=c;


		//and
		asm("and %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		//	c=a&b; 
		res=c;
		asm("and %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//or
		asm("or %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("or %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//xor
		asm("xor %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("xor %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//shift left logic
		asm("sll %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("sll %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right logic 
		asm("srl %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("srl %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		//shift left arithmetic
		asm("slt %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("slt %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right arithmetic
		asm("sra %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("sra %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer mul 
		asm("mul %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("mul %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer division
			asm("div %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		// integer unsigned division 
			asm("divu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		// integer module
				asm("rem %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;

		// integer unsigned module
		asm("remu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;




		// comparison 
		// comparison 
		// comparison 
	}

	return EXIT_SUCCESS;
}

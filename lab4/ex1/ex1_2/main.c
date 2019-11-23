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
		register  int a asm volatile(("x1")=pattern[i];
		register  int b asm volatile(("x2")=pattern[i];
		register  int c asm volatile(("x3");
		asm volatile( volatile("add  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile( volatile("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b+a;
		res=c;
		// immediate addition
		asm volatile( volatile("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0x3));
		res=c;


		// subtraction
		asm volatile( volatile ("sub  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile( volatile ("sub  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b-a;
		res=c;


		//and
		asm volatile( volatile ("and %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		//	c=a&b; 
		res=c;
		asm volatile( volatile("and %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//or
		asm volatile(("or %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("or %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//xor
		asm volatile(("xor %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("xor %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//shift left logic
		asm volatile(("sll %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("sll %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right logic 
		asm volatile(("srl %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("srl %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		//shift left arithmetic
		asm volatile(("slt %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("slt %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right arithmetic
		asm volatile(("sra %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("sra %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer mul 
		asm volatile(("mul %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("mul %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer division
			asm volatile(("div %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		// integer unsigned division 
			asm volatile(("divu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		// integer module
				asm volatile(("rem %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm volatile(("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;

		// integer unsigned module
		asm volatile(("remu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm volatile(("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;


		// nope
	asm volatile(("nop");	
		res=c;


		asm volatile( ("lui %0,%1": "=r" (c): "i" (0x000FF));
		res=c;
	

		asm volatile( ("auipc %0,%1": "=r" (c): "i" (0x000FF));
		res=c;
	
	// comparison 
		
		// comparison 
		// comparison 
	}
for ( i=0;i<6;i++) {
		// addition 	
		register  int a asm volatile(("x1")=~pattern[i];
		register  int b asm volatile(("x2")=~pattern[i];
		register  int c asm volatile(("x3");
		asm volatile(("add  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile(("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b+a;
		res=c;
		// immediate addition
		asm volatile(("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0x3));
		res=c;


		// subtraction
		asm volatile(("sub  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile(("sub  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b-a;
		res=c;


		//and
		asm volatile(("and %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		//	c=a&b; 
		res=c;
		asm volatile(("and %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//or
		asm volatile(("or %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("or %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//xor
		asm volatile(("xor %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("xor %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//shift left logic
		asm volatile(("sll %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("sll %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right logic 
		asm volatile(("srl %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("srl %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		//shift left arithmetic
		asm volatile(("slt %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("slt %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right arithmetic
		asm volatile(("sra %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("sra %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer mul 
		asm volatile(("mul %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("mul %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer division
			asm volatile(("div %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		// integer unsigned division 
			asm volatile(("divu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		// integer module
				asm volatile(("rem %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm volatile(("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;

		// integer unsigned module
		asm volatile(("remu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile(("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;




		// comparison 
		// comparison 
		// comparison 
	}

	return EXIT_SUCCESS;
}

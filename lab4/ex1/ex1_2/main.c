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
	register  int a ;
	register  int b;
	register  int c ;
	/*testing integer ALU */

	for ( i=0;i<6;i++) {
		// addition 	
		a =pattern[i];
		b =pattern[i];
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b+a;
		res=c;
		// immediate addition
		asm volatile("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0x0));
		res=c;


		// subtraction
		asm volatile("sub  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
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
		asm volatile("or %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("or %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//xor
		asm volatile("xor %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("xor %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//shift left logic
		asm volatile("sll %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("sll %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right logic 
		asm volatile("srl %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("srl %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		//shift left arithmetic
		asm volatile("slt %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("slt %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		//shift left arithmetic unsigned
		asm volatile("sltu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("sltu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right arithmetic
		asm volatile("sra %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("sra %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer mul 
		asm volatile("mul %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mul %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		asm volatile("mulhu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mulhu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		asm volatile("mulh %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mulh %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		asm volatile("mulhsu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mulhsu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;




		// integer division
		asm volatile("div %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		// integer unsigned division 
		asm volatile("divu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer module
		asm volatile("rem %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm volatile("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;

		// integer unsigned module
		asm volatile("remu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm volatile("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;


		// nope
		asm volatile("nop");	
		res=c;


		asm volatile ("lui %0,%1": "=r" (c): "n" (0x000FF));
		res=c;


		asm volatile ("auipc %0,%1": "=r" (c): "n" (0x000FF));
		res=c;

		//c=b+a;
		asm volatile("add  x0,%0,%1": : "r" (a),"r" (b) );
		res=c;
		asm volatile("add x0,%0,%1": : "r" (b),"r" (a) );
		//c=b+a;
		res=c;		
		// comparison

		asm volatile ("beq %0,%1,next\n\tnext:":: "r" (a), "r" (b));
		asm volatile ("beq %0,%1,next1\n\tnext1:":: "r" (b), "r" (a));

		asm volatile ("bne %0,%1,next2\n\tnext2:":: "r" (a), "r" (b));
		asm volatile ("bne %0,%1,next3\n\tnext3:":: "r" (b), "r" (a));	


		asm volatile ("blt %0,%1,next4\n\tnext4:":: "r" (a), "r" (b));
		asm volatile ("blt %0,%1,next5\n\tnext5:":: "r" (b), "r" (a));

		asm volatile ("bge %0,%1,next6\n\tnext6:":: "r" (a), "r" (b));
		asm volatile ("bge %0,%1,next7\n\tnext7:":: "r" (b), "r" (a));

		asm volatile ("bltu %0,%1,next8\n\tnext8:":: "r" (a), "r" (b));
		asm volatile ("bltu %0,%1,next9\n\tnext9:":: "r" (b), "r" (a));

		asm volatile ("bgeu %0,%1,next11\n\tnext11:":: "r" (a), "r" (b));
		asm volatile ("bgeu %0,%1,next12\n\tnext12:":: "r" (b), "r" (a));



		asm volatile ("li %0,%1": "=r" (c): "i" (0x3245));
		res=c;
		asm volatile ("mv %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("not %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("seqz %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("snez %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("sltz %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("sgtz %0,%1":"=r" (c): "r" (a));


		// pulp extension 
		asm volatile ("p.extract %0,%1,3,2": "=r" (c): "r" (a));
		res=c;	
		asm volatile ("p.extractu %0,%1,3,2": "=r" (c): "r" (a));
		res=c;	
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;		
		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	
		asm volatile ("p.insert %0,%1,3,2": "=r" (c): "r" (a));
		res=c;		
		asm volatile ("p.insertr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	

		asm volatile ("p.insertr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	

		asm volatile ("p.bclr %0,%1,3,2": "=r" (c): "r" (a));
		res=c;		
		asm volatile ("p.bclrr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.bclrr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	
		asm volatile ("p.bset %0,%1,3,2": "=r" (c): "r" (a));
		res=c;		
		asm volatile ("p.bsetr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.bsetr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	


		asm volatile ("p.ff1 %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.fl1 %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.clb %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.cnt %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.ror %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;

		asm volatile ("p.ror %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.abs %0,%1": "=r" (c): "r" (b) );
		res=c;




		asm volatile ("p.slet %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.slet %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.min %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.min %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.minu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.minu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.max %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.max %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.maxu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.maxu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.exths %0,%1": "=r" (c): "r" (a) );
		res=c;
		asm volatile ("p.exthz %0,%1": "=r" (c): "r" (b));
		res=c;

		asm volatile ("p.extbs %0,%1": "=r" (c): "r" (a) );
		res=c;
		asm volatile ("p.extbz %0,%1": "=r" (c): "r" (b) );
		res=c;

		asm volatile ("p.clip %0,%1,4": "=r" (c): "r" (a) );
		res=c;
		asm volatile ("p.clipr %0,%1,%2": "=r" (c):"r" (a), "r" (b));
		res=c;
		asm volatile ("p.clipr %0,%1,%2": "=r" (c):"r" (b), "r" (a));
		res=c;

		asm volatile ("p.clipu %0,%1,4": "=r" (c): "r" (b));
		res=c;

		asm volatile ("p.clipur %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.clipur %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		// arithmetic pulp extentions 

		asm volatile ("p.addN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addN %0,%1,%2,2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addN %0,%1,%2,2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.adduN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.adduRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.adduNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.adduRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		// sub
		asm volatile ("p.subN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subN %0,%1,%2,2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subN %0,%1,%2,2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.subuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subuNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subuRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		// multiplications 


		asm volatile ("p.mac %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mac %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.msu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.msu  %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.muls %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.muls %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhs %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhs %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.muluN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.muluN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.muluRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.muluRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.macsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.macsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.macuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.macuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;


		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;
		asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.dotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotsp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotsp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;


		asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;

		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;


		asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

	}


	//negated

	for ( i=0;i<6;i++) {
		// addition 	
		a =~pattern[i];
		b =~pattern[i];
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		//c=b+a;
		res=c;
		// immediate addition
		asm volatile("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0x0));
		res=c;


		// subtraction
		asm volatile("sub  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
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
		asm volatile("or %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("or %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//xor
		asm volatile("xor %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("xor %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		//shift left logic
		asm volatile("sll %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("sll %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right logic 
		asm volatile("srl %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("srl %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;



		//shift left arithmetic
		asm volatile("slt %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("slt %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		//shift left arithmetic unsigned
		asm volatile("sltu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("sltu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		//shift right arithmetic
		asm volatile("sra %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("sra %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer mul 
		asm volatile("mul %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mul %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		asm volatile("mulhu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mulhu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		asm volatile("mulh %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mulh %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;

		asm volatile("mulhsu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("mulhsu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;




		// integer division
		asm volatile("div %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;
		// integer unsigned division 
		asm volatile("divu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	

		res=c;
		asm volatile("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	

		res=c;


		// integer module
		asm volatile("rem %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm volatile("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;

		// integer unsigned module
		asm volatile("remu %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
		res=c;
		asm volatile("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));	
		res=c;


		// nope
		asm volatile("nop");	
		res=c;


		asm volatile ("lui %0,%1": "=r" (c): "n" (0x000FF));
		res=c;


		asm volatile ("auipc %0,%1": "=r" (c): "n" (0x000FF));
		res=c;

		//c=b+a;
		asm volatile("add  x0,%0,%1": : "r" (a),"r" (b) );
		res=c;
		asm volatile("add x0,%0,%1": : "r" (b),"r" (a) );
		//c=b+a;
		res=c;			asm volatile ("li %0,%1": "=r" (c): "i" (0x3245));
		res=c;
		asm volatile ("mv %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("not %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("seqz %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("snez %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("sltz %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("sgtz %0,%1":"=r" (c): "r" (a));


		// pulp extension 
		asm volatile ("p.extract %0,%1,3,2": "=r" (c): "r" (a));
		res=c;	
		asm volatile ("p.extractu %0,%1,3,2": "=r" (c): "r" (a));
		res=c;	
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;		
		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	
		asm volatile ("p.insert %0,%1,3,2": "=r" (c): "r" (a));
		res=c;		
		asm volatile ("p.insertr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	

		asm volatile ("p.insertr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	

		asm volatile ("p.bclr %0,%1,3,2": "=r" (c): "r" (a));
		res=c;		
		asm volatile ("p.bclrr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.bclrr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	
		asm volatile ("p.bset %0,%1,3,2": "=r" (c): "r" (a));
		res=c;		
		asm volatile ("p.bsetr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.bsetr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;	


		asm volatile ("p.ff1 %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.fl1 %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.clb %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.cnt %0,%1": "=r" (c): "r" (a));
		res=c;	

		asm volatile ("p.ror %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;

		asm volatile ("p.ror %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.abs %0,%1": "=r" (c): "r" (b) );
		res=c;




		asm volatile ("p.slet %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.slet %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.min %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.min %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.minu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.minu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.max %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.max %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.maxu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.maxu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.exths %0,%1": "=r" (c): "r" (a) );
		res=c;
		asm volatile ("p.exthz %0,%1": "=r" (c): "r" (b));
		res=c;

		asm volatile ("p.extbs %0,%1": "=r" (c): "r" (a) );
		res=c;
		asm volatile ("p.extbz %0,%1": "=r" (c): "r" (b) );
		res=c;

		asm volatile ("p.clip %0,%1,4": "=r" (c): "r" (a) );
		res=c;
		asm volatile ("p.clipr %0,%1,%2": "=r" (c):"r" (a), "r" (b));
		res=c;
		asm volatile ("p.clipr %0,%1,%2": "=r" (c):"r" (b), "r" (a));
		res=c;

		asm volatile ("p.clipu %0,%1,4": "=r" (c): "r" (b));
		res=c;

		asm volatile ("p.clipur %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.clipur %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		// arithmetic pulp extentions 

		asm volatile ("p.addN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addN %0,%1,%2,2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addN %0,%1,%2,2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.adduN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.adduRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.adduNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.addRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.addRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.adduRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.adduRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		// sub
		asm volatile ("p.subN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subN %0,%1,%2,2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subN %0,%1,%2,2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.subuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subuNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.subuRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.subuRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		// multiplications 


		asm volatile ("p.mac %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mac %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.msu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.msu  %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.muls %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.muls %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhs %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhs %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.muluN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.muluN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.muluRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.muluRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.mulhhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.mulhhuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("p.macsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.macsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.macuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.macuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.macuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("p.machhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("p.machhuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;
		asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.dotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotsp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.dotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.dotsp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;


		asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
		res=c;
		asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
		res=c;

		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;

		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;


		asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
	}



	return EXIT_SUCCESS;
}

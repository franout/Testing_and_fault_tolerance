#include <stdlib.h>
#include <stdio.h>
#define TEST_PATTERNS 16 
#define TEST_CORE 0

void f1(void);
void f2(void);
void f3(void);


int main ( void) {

	int pattern[TEST_PATTERNS]= {0x00000000,0x11111111,0x22222222,0x33333333,0x444444444,0x55555555,0x66666666,0x77777777,0x8888888,0x99999999,0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEE,0xFFFFFFFF};

	int i;
	volatile int res;
	volatile int a, b, c ;

	////////////////////////////////////////////////////
	///////////// TESTING EXECUTION UNIT ///////////////
	////////////////////////////////////////////////////
	for ( i=0;i<TEST_PATTERNS;i++) {
		a =pattern[i];
		//	for ( int j=i; j<TEST_PATTERNS-1;j++){
		// addition 	

		b =pattern[i];
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		res=c;

		// subtraction
		asm volatile("sub  %0,%1,%2": "=r" (c): "r" (a),"r" (b) );
		res=c;
		asm volatile ("sub  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		res=c;


		//and
		asm volatile ("and %0, %1 ,%2": "=r" (c): "r" (a), "r" (b));	
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

		// comparison
		asm volatile ("not %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("neg %0,%1":"=r" (c): "r" (a));
		res=c;
		// comparison
		asm volatile ("seqz %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("snez %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("sltz %0,%1":"=r" (c): "r" (a));
		res=c;
		asm volatile ("sgtz %0,%1":"=r" (c): "r" (a));
		res=c;
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




		//atomic instructions 

		// pulp extension 
		// bit manipulation
		asm volatile ("p.extract %0,%1,3,2": "=r" (c): "r" (a));
		res=c;	
		asm volatile ("p.extractu %0,%1,3,2": "=r" (c): "r" (a));
		res=c;	
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;		
		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;	
		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (b),"r" (a));
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
		// alu operations
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

		// immediat branching opeartions 
		asm volatile ("p.beqimm  %0,%1,%2\n\tno_jump_here:":: "r" (4),"i" (5), "i" (2) ); // not taken 
		asm volatile ("p.bneimm %0,%1,%2\n\tjump_here:"::"r" (4) , "i" (4) , "i" (2)); //taken


		// multiplications and mac ops
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
		// vectorial instrucctions 
		// alu instructions 
		asm volatile ("pv.addb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.addb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("pv.addh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.addh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("pv.sc.addb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.sc.addb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("pv.sc.addh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.sc.addh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("pv.sci.addb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
		res=c;
		asm volatile ("pv.sci.addb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
		res=c;

		asm volatile ("pv.sci.addh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
		res=c;
		asm volatile ("pv.sci.addh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
		res=c;

		asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
		res=c;
		asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
		res=c;
		asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
		res=c;
		asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
		res=c;


		asm volatile ("pv.avgb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.avgb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("pv.avgh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.avgh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		asm volatile ("pv.sc.avgb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.sc.avgb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("pv.sc.avgh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		asm volatile ("pv.sc.avgh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		asm volatile ("pv.sci.avgb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
		res=c;
		asm volatile ("pv.sci.avgb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
		res=c;

		asm volatile ("pv.sci.avgh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
		res=c;
		asm volatile ("pv.sci.avgh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
		res=c;


		asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
								res=c;
								asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
								res=c;

								asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
								res=c;
								asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
								res=c;

								asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
								res=c;
								asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
								res=c;

								asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
								res=c;
								asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
								res=c;

								asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
								res=c;
								asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
								res=c;

								asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
								res=c;
								asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
										res=c;



										asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
										res=c;
										asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
										res=c;

										asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
										res=c;
										asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
										res=c;

										asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
										res=c;
										asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
										res=c;

										asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
										res=c;
										asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
										res=c;

										asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
										res=c;
										asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
										res=c;

										asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
										res=c;
										asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
												res=c;



												asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
												res=c;
												asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
												res=c;

												asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
												res=c;
												asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
												res=c;

												asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
												res=c;
												asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
												res=c;

												asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
												res=c;
												asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
												res=c;

												asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
												res=c;
												asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
												res=c;

												asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
												res=c;
												asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
														res=c;



														asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
														res=c;
														asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
														res=c;

														asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
														res=c;
														asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
														res=c;

														asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
														res=c;
														asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
														res=c;

														asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
														res=c;
														asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
														res=c;

														asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
														res=c;
														asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
														res=c;

														asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
														res=c;
														asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																res=c;



																asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																res=c;
																asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																res=c;

																asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																res=c;
																asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																res=c;

																asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																res=c;
																asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																res=c;

																asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																res=c;
																asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																res=c;

																asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																res=c;
																asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																res=c;

																asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																res=c;
																asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																		res=c;



																		asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																		res=c;
																		asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																		res=c;

																		asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																		res=c;
																		asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																		res=c;

																		asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																		res=c;
																		asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																		res=c;

																		asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																		res=c;
																		asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																		res=c;

																		asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																		res=c;
																		asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																		res=c;

																		asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																		res=c;
																		asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																				res=c;



																				asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																				res=c;
																				asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																				res=c;

																				asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																				res=c;
																				asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																				res=c;

																				asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																				res=c;
																				asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																				res=c;

																				asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																				res=c;
																				asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																				res=c;

																				asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																				res=c;
																				asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																				res=c;

																				asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																				res=c;
																				asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																						res=c;



																						asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																						res=c;
																						asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																						res=c;

																						asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																						res=c;
																						asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																						res=c;

																						asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																						res=c;
																						asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																						res=c;

																						asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																						res=c;
																						asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																						res=c;

																						asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																						res=c;
																						asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																						res=c;

																						asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																						res=c;
																						asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																								res=c;



																								asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																								res=c;
																								asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																								res=c;

																								asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																								res=c;
																								asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																								res=c;

																								asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																								res=c;
																								asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																								res=c;

																								asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																								res=c;
																								asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																								res=c;

																								asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																								res=c;
																								asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																								res=c;

																								asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																								res=c;
																								asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																										res=c;



																										asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																										res=c;
																										asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																										res=c;

																										asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																										res=c;
																										asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																										res=c;

																										asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																										res=c;
																										asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																										res=c;

																										asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																										res=c;
																										asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																										res=c;

																										asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																										res=c;
																										asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																										res=c;

																										asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																										res=c;
																										asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																												res=c;



																												asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																												res=c;
																												asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																												res=c;

																												asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																												res=c;
																												asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																												res=c;

																												asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																												res=c;
																												asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																												res=c;

																												asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																												res=c;
																												asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																												res=c;

																												asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																												res=c;
																												asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																												res=c;

																												asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																												res=c;
																												asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																														res=c;



																														asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																														res=c;
																														asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																														res=c;

																														asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																														res=c;
																														asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																														res=c;

																														asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																														res=c;
																														asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																														res=c;

																														asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																														res=c;
																														asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																														res=c;

																														asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																														res=c;
																														asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																														res=c;

																														asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																														res=c;
																														asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																																res=c;



																																asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																res=c;
																																asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																res=c;

																																asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																res=c;
																																asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																res=c;

																																asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																res=c;
																																asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																res=c;

																																asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																res=c;
																																asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																res=c;

																																asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																																res=c;
																																asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																																res=c;

																																asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																																res=c;
																																asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																																		res=c;



																																		asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																		res=c;
																																		asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																		res=c;

																																		asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																		res=c;
																																		asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																		res=c;

																																		asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																		res=c;
																																		asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																		res=c;

																																		asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																		res=c;
																																		asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																		res=c;

																																		asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																																		res=c;
																																		asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																																		res=c;

																																		asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																																		res=c;
																																		asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																																				res=c;



																																				asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																				res=c;
																																				asm volatile ("pv.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																				res=c;

																																				asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																				res=c;
																																				asm volatile ("pv.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																				res=c;

																																				asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																				res=c;
																																				asm volatile ("pv.sc.subb %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																				res=c;

																																				asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
																																				res=c;
																																				asm volatile ("pv.sc.subh %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
																																				res=c;

																																				asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																																				res=c;
																																				asm volatile ("pv.sci.subb %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f));
																																				res=c;

																																				asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (a) , "i" (0x00f));
																																				res=c;
																																				asm volatile ("pv.sci.subh %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00f);
																																						res=c;














																																						//dot products
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
	// immediat instructions
	asm volatile("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0x000f));
	res=c;
	asm volatile ("slti %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	asm volatile ("sltiu  %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	asm volatile("xori %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	asm volatile("ori %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	asm volatile ("andi %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	asm volatile("slli %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	asm volatile("srli %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	asm volatile("srai %0,%1,%2": "=r" (c): "r" (a), "i" (0x000f));
	res=c;
	// csr instructions
	asm volatile ("rdcycleh x3\n\trdcycle %0\n\trdcycleh x4":"=r" (c));
	res=c;
	asm volatile ("rdtime %0": "=r" (c));
	res=c;
	asm volatile ("rdinstret %0": "=r" (c));
	res =c;
	/// hardware counters from 3 to 31 read and write all 1s

	asm volatile ("csrr %0,hpmcounter3": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter3,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter4": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter4,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter5": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter5,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter6": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter6,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter7": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter7,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter8": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter8,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter9": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter9,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter10": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter10,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter11": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter11,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter12": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter12,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter13": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter13,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter14": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter14,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter15": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter15,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter16": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter16,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter17": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter17,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter18": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter18,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter19": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter19,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter20": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter20,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter21": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter21,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter22": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter22,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter23": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter23,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter24": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter24,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter25": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter25,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter26": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter26,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter27": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter27,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter28": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter28,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter29": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter29,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter30": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter30,%0":: "i" (0x0000ffff));

	asm volatile ("csrr %0,hpmcounter31": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter31,%0":: "i" (0x0000ffff));
	// set and clear a specifi bit of a csr register
	asm volatile ("csrs hpmcounter31,%0":: "r" (3));
	asm volatile ("csrc hpmcounter31, %0":: "r" (3));

	/*
	   asm volatile ("csrr %0,ustatus": "=r" (c));	//user status register.
	   res=c;
	   asm volatile ("csrr %0,uie": "=r" (c));	 // user interrupt enable register
	   res=c;


	   asm volatile ("csrr %0, utvec": "=r" (c)); // User trap handler base address.
	   res=c;
	   asm volatile ("csrr %0,uscratch": "=r" (c)); // Scratch register for user trap handlers.
	   res=c;
	   asm volatile ("csrr %0,uepc": "=r" (c)); // User exception program counter.
	   res=c;
	   asm volatile ("csrr %0, ucause": "=r" (c)); // User trap cause.
	   res=c;
	   asm volatile ("csrr %0, utval": "=r" (c)); // User bad address or instruction.
	   res=c;
	   asm volatile ("csrr %0,uip": "=r" (c)); 
	   res=c;*/
	// nope
	asm volatile("nop");// converted into  addi x0,x0,0	
	res=c;


	///////////////////////////////////////////////////
	//////////// TESTING REST OF CORE /////////////////
	///////////////////////////////////////////////////
#if TEST_CORE	
	asm volatile ("li %0,%1": "=r" (c): "i" (0x3245));
	res=c;
	asm volatile ("mv %0,%1":"=r" (c): "r" (a));
	res=c;

	asm volatile ("auipc %0,%1": "=r" (c): "n" (0x000FF));
	res=c;	

	asm volatile ("lui %0,%1": "=r" (c): "n" (0x000FF));
	res=c;
	// hint instructions
	asm volatile ("lui r0,%0": : "i" (0x000ff));
	asm volatile ("auipc r0,%0":: "i" (0x000ff));
	asm volatile ("andi r0,%0,%1"::"r" (a), "i" (0x000ff));
	asm volatile ("ori r0,%0,%1":: "r" (a),"i" (0x000ff));
	asm volatile ("xori r0,%0,%1"::"r" (a), "i" (0x000ff));
	asm volatile ("add r0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("sub r0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("and r0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("or r0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("xor r0,%0,%1"::"r" (a), "r" (b));

	asm volatile ("sll r0,%0,%1":: "i" (0x000ff));
	asm volatile ("srl r0,%0":: "i" (0x000ff));
	asm volatile ("sra r0,%0":: "i" (0x000ff));
	asm volatile ("fence r0,%0":: "i" (0x000ff));
	asm volatile ("slti r0,%0":: "i" (0x000ff));
	asm volatile ("sltiu r0,%0":: "i" (0x000ff));
	asm volatile ("slli r0,%0":: "i" (0x000ff));
	asm volatile ("srli r0,%0":: "i" (0x000ff));
	asm volatile ("srai r0,%0":: "i" (0x000ff));
	asm volatile ("slt r0,%0":: "i" (0x000ff));
	asm volatile ("sltu r0,%0":: "i" (0x000ff));

	asm volatile ("fence.I");
	// atomic memory operations
	asm volatile ("amoswap.w.aq t0, t0, (0x2222)"); 
	// compressed instructions 

	// load and store instructions (pulp extension)

	// hardware loops 

	f1();
#endif
	return EXIT_SUCCESS;
	}



	// checking the subroutins calls and returns 
	void f1(void ) {
		f2();
	}

	void f2(void) {
		f3();
	}
	void f3(void){
		asm volatile("nop");
	}

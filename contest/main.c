#include <stdlib.h>
#include <stdio.h>

#define TEST_PATTERNS 17
#define TEST_PATTERNS_DIV 4
#define TEST_CORE 0 



#if TEST_CORE
void __attribute__((noinline)) f1(void);
void __attribute__((noinline)) f2(void);
void __attribute__((noinline)) f3(void);
int __attribute__((noinline)) f4(int par);

extern int * vector_table;

int __attribute__((inline)) rt_irq_disable(){
	asm volatile ("csrc mstatus, %0":: "r" (3));
	asm volatile ("csrc mstatus, %0":: "r" (0));
	return 0;

}

int __attribute__((inline)) rt_irq_enable(){
	asm volatile ("csrs mstatus, %0":: "r" (3));
	asm volatile ("csrs mstatus, %0":: "r" (0));
	return 0;
}
//64 bytes protection pmp
static volatile unsigned char protected_data[64];
static volatile unsigned int return_here_instr;

static volatile unsigned int __attribute__ ((aligned (4))) stack_data[31];
void __attribute__((inline)) my_dataerr_handler();
void __attribute__((inline)) my_exception();
#define PUSH_ALL "sw x1,  0(x18)\n" \
	"sw x9,  32(x18)\n" \
"sw x10, 36(x18)\n" \
"sw x11, 40(x18)\n" \
"sw x12, 44(x18)\n" \
"sw x13, 48(x18)\n" \
"sw x14, 52(x18)\n" \
"sw x15, 56(x18)\n" \
"sw x16, 60(x18)\n" \
"sw x17, 64(x18)\n" \

#define POP_ALL  "lw x1,  0(x18)\n" \
	"lw x9,  32(x18)\n" \
"lw x10, 36(x18)\n" \
"lw x11, 40(x18)\n" \
"lw x12, 44(x18)\n" \
"lw x13, 48(x18)\n" \
"lw x14, 52(x18)\n" \
"lw x15, 56(x18)\n" \
"lw x16, 60(x18)\n" \
"lw x17, 64(x18)\n" \

#define INSTR_ACC_FAULT  1
#define ILLEGAL_INSTR    2
#define LOAD_ACC_FAULT   5
#define STORE_ACC_FAULT  7
#define ECALL_MCAUSE     11
#define ECALL_UCAUSE     8

int check_load_tor(void);

#endif



int main ( void) {

	int pattern[TEST_PATTERNS]= {
		0x00000000, 0x00000001,0x11111111,0x22222222,0x33333333,0x444444444,
		0x55555555, 0x66666666,0x77777777,0x88888888,0x999999999,
		0xAAAAAAAA ,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEEE,
		0xFFFFFFFF
	};
	int pattern_div[TEST_PATTERNS_DIV]={0,-1,0x0FFFFFFF,0xF0000001};
	volatile int a, b, c ;
	volatile int res;
	int i=0;
	////////////////////////////////////////////////////
	///////////// TESTING EXECUTION UNIT ///////////////
	///////////////////////////////////////////////////
	for ( i=0;i<TEST_PATTERNS;i++) {
		a =pattern[i];
		// addition
		b =~pattern[i];
		// + ->reading and writing  , = -> overwrite an existing register
		asm volatile("add  %0,%1,%2": "+r" (c): "r" (a),"r" (b) );
		res=c;
		b=pattern[i];
		asm volatile("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		res=c;

		// subtraction
		b =~pattern[i];
		asm volatile("sub  %0,%1,%2": "+r" (c): "r" (a),"r" (b) );
		res=c;b=pattern[i];

		asm volatile ("sub  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
		res=c;


		//and
		b =~pattern[i];
		asm volatile ("and %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		res=c;
		b=pattern[i];
		asm volatile("and %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
		res=c;

		//or
		b =~pattern[i];

		asm volatile("or %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));

		res=c;
		b =pattern[i];

		asm volatile("or %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;

		//xor
		b =~pattern[i];

		asm volatile("xor %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("xor %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;

		//shift left logic
		b =~pattern[i];

		asm volatile("sll %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("sll %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;


		//shift right logic
		b =~pattern[i];

		asm volatile("srl %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("srl %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;



		//shift left arithmetic
		b =~pattern[i];

		asm volatile("slt %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("slt %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;
		//shift left arithmetic unsigned
		b =~pattern[i];

		asm volatile("sltu %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("sltu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;

		//shift right arithmetic
		b =~pattern[i];

		asm volatile("sra %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("sra %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;

		// integer mul
		b =~pattern[i];

		asm volatile("mul %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("mul %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;
		b =~pattern[i];

		asm volatile("mulhu %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		b =~pattern[i];

		asm volatile("mulhu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
		b =~pattern[i];

		res=c;
		b =~pattern[i];

		asm volatile("mulh %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("mulh %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;
		b =~pattern[i];

		asm volatile("mulhsu %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));

		b =pattern[i];
		res=c;
		asm volatile("mulhsu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
		res=c;
		// integer division
		b =~pattern[i];

		asm volatile("div %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;
		// integer unsigned division
		b =~pattern[i];

		asm volatile("divu %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =~pattern[i];

		res=c;
		asm volatile("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));

		res=c;


		// integer module
		b =~pattern[i];

		asm volatile("rem %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
		res=c;

		// integer unsigned module
		b =~pattern[i];

		asm volatile("remu %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
		b =pattern[i];

		res=c;
		asm volatile("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
		res=c;

		asm volatile ("not %0,%1":"+r" (c): "r" (a));
		a=~pattern[i];
		res=c;
		asm volatile ("not %0,%1":"+r" (c): "r" (a));
		res=c;
		asm volatile ("neg %0,%1":"+r" (c): "r" (a));
		res=c;
		a=pattern[i];
		asm volatile ("neg %0,%1":"+r" (c): "r" (a));

		// comparison
		asm volatile ("seqz %0,%1":"=r" (c): "r" (a));
		a=~pattern[i];
		res=c;
		asm volatile ("seqz %0,%1":"=r" (c): "r" (a));
		a=pattern[i];
		res=c;
		asm volatile ("snez %0,%1":"=r" (c): "r" (a));
		a=~pattern[i];
		res=c;
		asm volatile ("snez %0,%1":"=r" (c): "r" (a));
		a=pattern[i];
		res=c;


		asm volatile ("sltz %0,%1":"=r" (c): "r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("sltz %0,%1":"=r" (c): "r" (a));
		res=c;
		a=pattern[i];

		asm volatile ("sgtz %0,%1":"=r" (c): "r" (a));
		res=c;
		res=c;
		a=~pattern[i];
		asm volatile ("sgtz %0,%1":"=r" (c): "r" (a));
		res=c;
		a=pattern[i];

		asm volatile ("beq %0,%1,next\n\tnext:":: "r" (a), "r" (b));
		b=~pattern[i];
		asm volatile ("beq %0,%1,next1\n\tnext1:":: "r" (b), "r" (a));

		b=pattern[i];
		asm volatile ("bne %0,%1,next2\n\tnext2:":: "r" (a), "r" (b));
		b=~pattern[i];
		asm volatile ("bne %0,%1,next3\n\tnext3:":: "r" (b), "r" (a));

		b=pattern[i];
		asm volatile ("blt %0,%1,next4\n\tnext4:":: "r" (a), "r" (b));
		b=~pattern[i];
		asm volatile ("blt %0,%1,next5\n\tnext5:":: "r" (b), "r" (a));

		b=pattern[i];
		asm volatile ("bge %0,%1,next6\n\tnext6:":: "r" (a), "r" (b));
		b=~pattern[i];
		asm volatile ("bge %0,%1,next7\n\tnext7:":: "r" (b), "r" (a));


		b=pattern[i];

		asm volatile ("bltu %0,%1,next8\n\tnext8:":: "r" (a), "r" (b));
		b=~pattern[i];

		asm volatile ("bltu %0,%1,next9\n\tnext9:":: "r" (b), "r" (a));

		b=pattern[i];
		asm volatile ("bgeu %0,%1,next11\n\tnext11:":: "r" (a), "r" (b));
		b=~pattern[i];
		asm volatile ("bgeu %0,%1,next12\n\tnext12:":: "r" (b), "r" (a));


	}

	// pulp extension
	// bit manipulation

	for(i=0;i<TEST_PATTERNS;i++) {
		a=pattern[i];
		b=~pattern[i];
		asm volatile ("p.extract %0,%1,3,2": "=r" (c): "r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("p.extract %0,%1,3,2": "=r" (c): "r" (a));
		res=c;

		a=pattern[i];
		asm volatile ("p.extractu %0,%1,3,2": "=r" (c): "r" (a));
		res=c;
		b=pattern[i];
		asm volatile ("p.extractu %0,%1,3,2": "=r" (c): "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.extractr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.extractur %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("p.insert %0,%1,3,2": "=r" (c): "r" (a));
		a=pattern[i];
		res=c;
		asm volatile ("p.insert %0,%1,3,2": "=r" (c): "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.insertr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.insertr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;

		a=~pattern[i];
		asm volatile ("p.bclr %0,%1,3,2": "=r" (c): "r" (a));
		res=c;
		a=pattern[i];
		asm volatile ("p.bclr %0,%1,3,2": "=r" (c): "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.bclrr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.bclrr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;

		a=~pattern[i];
		asm volatile ("p.bset %0,%1,3,2": "=r" (c): "r" (a));
		res=c;
		a=pattern[i];
		asm volatile ("p.bset %0,%1,3,2": "=r" (c): "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.bsetr %0,%1,%2": "=r" (c): "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.bsetr %0,%1,%2": "=r" (c): "r" (b),"r" (a));
		res=c;


		asm volatile ("p.ff1 %0,%1": "=r" (c): "r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("p.ff1 %0,%1": "=r" (c): "r" (a));
		res=c;

		a=pattern[i];
		asm volatile ("p.fl1 %0,%1": "=r" (c): "r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("p.fl1 %0,%1": "=r" (c): "r" (a));
		res=c;


		a=pattern[i];
		asm volatile ("p.fl1 %0,%1": "=r" (c): "r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("p.fl1 %0,%1": "=r" (c): "r" (a));
		res=c;

		a=pattern[i];
		asm volatile ("p.clb %0,%1": "=r" (c): "r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("p.clb %0,%1": "=r" (c): "r" (a));
		res=c;

		a=pattern[i];
		asm volatile ("p.cnt %0,%1": "=r" (c): "r" (a));
		res=c;
		a=~pattern[i];
		asm volatile ("p.cnt %0,%1": "=r" (c): "r" (a));
		res=c;


		asm volatile ("p.ror %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.ror %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		// alu operations
		b=~pattern[i];
		asm volatile ("p.abs %0,%1": "=r" (c): "r" (a) );
		res=c;
		b=pattern[i];
		asm volatile ("p.abs %0,%1": "=r" (c): "r" (a));
		res=c;

		b=pattern[i];
		asm volatile ("p.slet %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=~pattern[i];
		asm volatile ("p.slet %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.min %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.min %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("p.minu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.minu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.max %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.max %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("p.maxu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.maxu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		asm volatile ("p.exths %0,%1": "=r" (c): "r" (a) );
		res=c;
		a=~pattern[i];
		asm volatile ("p.exths %0,%1": "=r" (c): "r" (a) );
		res=c;

		b=~pattern[i];
		asm volatile ("p.exthz %0,%1": "=r" (c): "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.exthz %0,%1": "=r" (c): "r" (b));
		res=c;

		a=pattern[i];
		asm volatile ("p.extbs %0,%1": "=r" (c): "r" (a) );
		res=c;
		a=~pattern[i];
		asm volatile ("p.extbs %0,%1": "=r" (c): "r" (a) );
		res=c;

		b=~pattern[i];
		asm volatile ("p.extbz %0,%1": "=r" (c): "r" (b) );
		res=c;
		b=pattern[i];
		asm volatile ("p.extbz %0,%1": "=r" (c): "r" (b) );
		res=c;

		a=pattern[i];
		asm volatile ("p.clip %0,%1,4": "=r" (c): "r" (a) );
		res=c;
		a=~pattern[i];
		asm volatile ("p.clip %0,%1,4": "=r" (c): "r" (a) );
		res=c;

		b=~pattern[i];
		asm volatile ("p.clipr %0,%1,%2": "=r" (c):"r" (a), "r" (b));
		res=c;
		b=pattern[i];

		asm volatile ("p.clipr %0,%1,%2": "=r" (c):"r" (b), "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.clipu %0,%1,4": "=r" (c): "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.clipu %0,%1,4": "=r" (c): "r" (b));
		res=c;
		b=~pattern[i];
		asm volatile ("p.clipu %0,%1,4": "=r" (c): "r" (b));
		res=c;


		asm volatile ("p.clipur %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.clipur %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		// arithmetic pulp extentions
		b=~pattern[i];
		asm volatile ("p.addN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.addN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.addN %0,%1,%2,2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.addN %0,%1,%2,2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.adduN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.adduN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.addRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.addRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.adduRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.adduRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.addNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.addNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.adduNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.adduNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.addRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.addRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.adduRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.adduRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		// sub
		b=~pattern[i];
		asm volatile ("p.subN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subN %0,%1,%2,2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subN %0,%1,%2,2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subuNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subuNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.subuRNr %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.subuRNr %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		// multiplications and mac ops
		b=~pattern[i];
		asm volatile ("p.mac %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("p.mac %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.msu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.msu  %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.muls %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.muls %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulhhs %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulhhs %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulhhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulhhsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulhhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulhhsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulhhu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulhhu %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.muluN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.muluN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulhhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulhhuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.muluRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.muluRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.mulhhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.mulhhuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.macsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.macsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.machhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.machhsN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.macsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.macsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.machhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.machhsRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.macuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.macuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.machhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.machhuN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.macuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.macuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("p.machhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("p.machhuRN %0,%1,%2,3": "=r" (c): "r" (b) , "r" (a));
		res=c;		


		// vectorial instrucctions
		// alu instructions
		b=~pattern[i];
		asm volatile ("pv.add.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.add.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.add.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("pv.add.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.add.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("pv.add.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.add.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("pv.add.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.add.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.add.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.add.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.add.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sub.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sub.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sub.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sub.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sub.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sub.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sub.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sub.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sub.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sub.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sub.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sub.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.avg.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("pv.avg.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avg.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avg.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.avg.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avg.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avg.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avg.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avg.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avg.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avg.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avg.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.avgu.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("pv.avgu.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avgu.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avgu.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;b=~pattern[i];
		asm volatile ("pv.avgu.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avgu.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avgu.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avgu.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avgu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avgu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.avgu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.avgu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.min.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("pv.min.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.min.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.min.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.min.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.min.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.min.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.min.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.min.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.min.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.min.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.min.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.minu.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.minu.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.minu.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;b=pattern[i];
		asm volatile ("pv.minu.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.minu.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.minu.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.minu.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.minu.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.minu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.minu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.minu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.minu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.max.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.max.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.max.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.max.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.max.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.max.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.max.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.max.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.max.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.max.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.max.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.max.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.maxu.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.maxu.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.maxu.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.maxu.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.maxu.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.maxu.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.maxu.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.maxu.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.maxu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.maxu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.maxu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.maxu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.srl.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.srl.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.srl.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.srl.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.srl.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.srl.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.srl.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.srl.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.srl.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.srl.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.srl.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.srl.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.sra.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sra.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sra.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sra.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sra.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sra.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sra.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sra.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.sra.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sra.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sra.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sra.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.sll.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sll.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sll.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sll.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sll.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sll.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sll.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sll.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.sll.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sll.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sll.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sll.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.or.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.or.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.or.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.or.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.or.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.or.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.or.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.or.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.or.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.or.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.or.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.or.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;



		b=~pattern[i];
		asm volatile ("pv.xor.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.xor.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.xor.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.xor.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.xor.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.xor.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.xor.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.xor.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.xor.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.xor.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.xor.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.xor.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.and.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.and.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.and.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.and.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.and.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.and.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.and.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.and.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.and.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.and.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.and.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00F));
		res=c;
		b=pattern[i];
		asm volatile ("pv.and.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x000));
		res=c;



		asm volatile ("pv.insert.b %0,%1,%2": "=r" (c):"r" (a), "i" (2));
		res=c;
		a=~pattern[i];
		asm volatile ("pv.insert.h %0,%1,%2": "=r" (c): "r" (a),"i" (1));
		res=c;

		a=pattern[i];
		asm volatile ("pv.extract.b %0,%1,%2": "=r" (c):  "r" (a), "i" (1));
		res=c;
		a=~pattern[i];
		asm volatile ("pv.extract.h %0,%1,%2": "=r" (c):  "r" (a), "i" (0));
		res=c;
		a=pattern[i];
		asm volatile ("pv.extractu.b %0,%1,%2": "=r" (c):  "r" (a),"i" (1));
		res=c;
		a=~pattern[i];
		asm volatile ("pv.extractu.h %0,%1,%2": "=r" (c): "r" (a), "i" (0));
		res=c;





		// dot products
		b=~pattern[i];
		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.dotup.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotup.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotup.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotup.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotup.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotup.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.dotusp.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotusp.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotusp.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotusp.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.dotusp.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.dotusp.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;



		b=~pattern[i];
		asm volatile ("pv.sdotup.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotup.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotup.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotup.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotup.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotup.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;


		b=~pattern[i];
		asm volatile ("pv.sdotusp.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotusp.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotusp.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotusp.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotusp.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotusp.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;



		b=~pattern[i];
		asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.sdotsp.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotsp.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotsp.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotsp.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.sdotsp.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (15));
		res=c;
		b=pattern[i];
		asm volatile ("pv.sdotsp.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;



		// shuffle and pack instructions

		b=~pattern[i];

		asm volatile ("pv.shuffle.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.shuffle.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.shuffle.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;
		asm volatile ("pv.shuffle.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (15));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		asm volatile ("pv.shuffleI0.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
		res=c;
		asm volatile ("pv.shuffleI0.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.shuffleI1.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
		res=c;
		asm volatile ("pv.shuffleI1.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;
		asm volatile ("pv.shuffleI2.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
		res=c;
		b=pattern[i];
		asm volatile ("pv.shuffleI2.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;
		asm volatile ("pv.shuffleI3.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
		res=c;
		asm volatile ("pv.shuffleI3.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.shuffle2.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.shuffle2.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		b=~pattern[i];
		asm volatile ("pv.pack.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.pack.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;
		b=~pattern[i];
		asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
		res=c;
		b=pattern[i];
		asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
		res=c;

		// vectorial comparison operations
		b=~pattern[i];
		asm volatile("pv.cmpeq.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;
		b=pattern[i];
		asm volatile("pv.cmpeq.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpeq.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpeq.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpeq.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpeq.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpeq.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpeq.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpeq.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpeq.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpeq.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpeq.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmpgt.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgt.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgt.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgt.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgt.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgt.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgt.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgt.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgt.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgt.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgt.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgt.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmpge.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpge.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpge.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpge.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpge.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpge.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpge.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpge.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpge.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpge.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpge.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpge.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmplt.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmplt.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmplt.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmplt.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmplt.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmplt.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmplt.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmplt.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmplt.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmplt.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmplt.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmplt.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmple.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmple.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmple.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmple.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmple.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmple.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmple.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmple.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmple.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmple.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmple.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmple.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmpgtu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgtu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgtu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgtu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgtu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgtu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgtu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgtu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgtu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgtu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgtu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgtu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmpgeu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgeu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgeu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgeu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgeu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgeu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgeu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgeu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgeu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgeu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpgeu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpgeu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmpltu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpltu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpltu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpltu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpltu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpltu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpltu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpltu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpltu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpltu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpltu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpltu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;
		b=~pattern[i];
		asm volatile("pv.cmpleu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpleu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpleu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpleu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpleu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpleu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpleu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpleu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpleu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpleu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x0a)  );
		res=c;b=~pattern[i];
		asm volatile("pv.cmpleu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (0x00)  );
		res=c;b=pattern[i];
		asm volatile("pv.cmpleu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (0x05)  );
		res=c;

		// immediat instructions
		asm volatile("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (0));
		res=c;
		a=res;
		asm volatile ("slti %0,%1,%2": "=r" (c): "r" (a), "i" (15));
		res=c;
		a=res;
		asm volatile ("sltiu  %0,%1,%2": "=r" (c): "r" (a), "i" (0));
		res=c;
		a=res;
		asm volatile("xori %0,%1,%2": "=r" (c): "r" (a), "i" (15));
		res=c;
		a=res;
		asm volatile("ori %0,%1,%2": "=r" (c): "r" (a), "i" (0));
		res=c;
		a=res;
		asm volatile ("andi %0,%1,%2": "=r" (c): "r" (a), "i" (15));
		res=c;
		a=res;
		asm volatile("slli %0,%1,%2": "=r" (c): "r" (a), "i" (0));
		res=c;
		a=res;
		asm volatile("srli %0,%1,%2": "=r" (c): "r" (a), "i" (15));
		res=c;
		a=res;
		asm volatile("srai %0,%1,%2": "=r" (c): "r" (a), "i" (0));
		res=c;
		a=res;

	}

	// multiplication and division full test
	for(i=0;i<TEST_PATTERNS_DIV;i++) {
		a=pattern_div[i];
		for(int j=i;j<TEST_PATTERNS_DIV;j++) {
			b=pattern_div[j];

			// integer division
			asm volatile("div %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
			res=c;
			asm volatile("div %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
			res=c;
			// integer unsigned division
			asm volatile("divu %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));
			res=c;
			asm volatile("divu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
			res=c;


			// integer module

			asm volatile("rem %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));

			res=c;
			asm volatile("rem %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
			res=c;

			// integer unsigned module

			asm volatile("remu %0, %1 ,%2": "+r" (c): "r" (a), "r" (b));

			res=c;
			asm volatile("remu %0, %1 ,%2": "=r" (c): "r" (b), "r" (a));
			res=c;



		}

	}

	// csr instructions
	asm volatile ("rdcycle %0":"=r" (c));
	res=c;
	asm volatile ("rdtime %0": "=r" (c));
	res=c;
	asm volatile ("rdinstret %0": "=r" (c));
	res =c;
	/// hardware counters from 3 to 31 read and write

	asm volatile ("csrr %0,hpmcounter3": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter3,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter3": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter3,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter3": "=r" (c));
	res =c;

	asm volatile ("csrr %0,hpmcounter4": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter4,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter4": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter4,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter4": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter5": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter5,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter5": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter5,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter5": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter6": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter6,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter6": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter6,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter6": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter7": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter7,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter7": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter7,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter7": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter8": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter8,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter8": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter8,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter8": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter9": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter9,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter9": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter9,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter9": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter10": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter10,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter10": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter10,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter10": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter11": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter11,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter11": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter11,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter11": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter12": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter12,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter12": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter12,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter12": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter13": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter13,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter13": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter13,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter13": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter14": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter14,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter14": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter14,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter14": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter15": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter15,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter15": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter15,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter15": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter16": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter16,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter16": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter16,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter16": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter17": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter17,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter17": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter17,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter17": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter18": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter18,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter18": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter18,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter18": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter19": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter19,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter19": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter19,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter19": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter20": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter20,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter20": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter20,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter20": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter21": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter21,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter21": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter21,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter21": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter22": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter22,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter22": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter22,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter22": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter23": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter23,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter23": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter23,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter23": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter24": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter24,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter24": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter24,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter24": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter25": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter25,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter25": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter25,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter25": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter26": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter26,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter26": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter26,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter26": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter27": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter27,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter27": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter27,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter27": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter28": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter28,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter28": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter28,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter28": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter29": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter29,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter29": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter29,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter29": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter30": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter30,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter30": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter30,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter30": "=r" (c));
	res =c;


	asm volatile ("csrr %0,hpmcounter31": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter31,%0":: "i" (0xFFFFFFFF));
	asm volatile ("csrr %0,hpmcounter31": "=r" (c));
	res =c;
	asm volatile ("csrw hpmcounter31,%0":: "i" (0x00000000));
	asm volatile ("csrr %0,hpmcounter31": "=r" (c));
	res =c;



	// set and clear a specifi bit of a csr register
	asm volatile ("csrs hpmcounter31,%0":: "r" (15));
	asm volatile ("csrc hpmcounter31, %0":: "r" (0));


	asm volatile ("csrr %0,mstatus":"=r" (c));
	res=c;
	asm volatile ("csrw mstatus,%0":: "r" (c));
	asm volatile ("csrr %0,mstatus":"=r" (c));
	res=c;

	asm volatile ("csrr %0,mtvec":"=r" (c));
	res=c;


	asm volatile ("csrr %0,mepc":"=r" (c));
	res=c;
	asm volatile ("csrw mepc,%0":: "r" (c));
	asm volatile ("csrr %0,mepc":"=r" (c));
	res=c;


	asm volatile ("csrr %0,mcause":"=r" (c));
	res=c;
	asm volatile ("csrw mcause,%0":: "r" (c));
	asm volatile ("csrr %0,mcause":"=r" (c));
	res=c;
	// csr for priviledge level
	asm volatile ("csrr %0,0xc10":"=r" (c));
	res=c;

	// csr for uhartid
	asm volatile ("csrr %0,0x014":"=r" (c));
	res=c;

	//csr for mhartid
	asm volatile ("csrr %0,0xf14":"=r" (c));
	res=c;


	asm volatile ("csrr %0,dcsr":"=r" (c));
	res=c;
	asm volatile ("csrw dcsr,%0":: "r" (c));
	asm volatile ("csrr %0,dcsr":"=r" (c));
	res=c;


	asm volatile ("csrr %0,dpc":"=r" (c));
	res=c;
	asm volatile ("csrw dpc,%0":: "r" (c));
	asm volatile ("csrr %0,dpc":"=r" (c));
	res=c;

	// csr for debug scrach 0
	asm volatile ("csrr %0,0x7b2":"=r" (c));
	res=c;
	asm volatile ("csrw 0x7b2,%0":: "r" (c));
	asm volatile ("csrr %0,0x7b2":"=r" (c));
	res=c;
	// csr for debug scratch 1
	asm volatile ("csrr %0,0x7b3":"=r" (c));
	res=c;
	asm volatile ("csrw 0x7b3,%0":: "r" (c));
	asm volatile ("csrr %0,0x7b3":"=r" (c));
	res=c;

	// user csr

	asm volatile ("csrr %0,0x000": "=r" (c));	//user status register.
	res=c;
	asm volatile ("csrw 0x000,%0"::"r" (c));
	asm volatile ("csrr %0,0x000": "=r" (c));	//user status register.
	res=c;

	asm volatile ("csrr %0, 0x005": "=r" (c)); // User trap handler base address.
	res=c;
	asm volatile ("csrw 0x005,%0"::"r" (c));
	asm volatile ("csrr %0, 0x005": "=r" (c)); // User trap handler base address.
	res=c;

	asm volatile ("csrr %0,0x040": "=r" (c)); // Scratch register for user trap handlers.
	res=c;
	asm volatile ("csrw 0x040,%0"::"r" (c));
	asm volatile ("csrr %0,0x040": "=r" (c)); // Scratch register for user trap handlers.
	res=c;

	asm volatile ("csrr %0,0x041": "=r" (c)); // User exception program counter.
	res=c;
	asm volatile ("csrw 0x041,%0":: "r" (c));
	asm volatile ("csrr %0,0x041": "=r" (c)); // User exception program counter.
	res=c;

	asm volatile ("csrr %0, 0x042": "=r" (c)); // User trap cause.
	res=c;
	asm volatile ("csrw 0x042,%0":: "r" (c));
	asm volatile ("csrr %0, 0x042": "=r" (c)); // User trap cause.
	res=c;

	asm volatile ("csrr %0, 0x043": "=r" (c)); // User bad address or instruction.
	res=c;
	asm volatile ("csrw 0x043,%0":: "r" (c));
	asm volatile ("csrr %0, 0x043": "=r" (c)); // User bad address or instruction.
	res=c;

	asm volatile ("csrr %0,0x044": "=r" (c)); // user interrupt pending
	res=c;
	asm volatile ("csrw 0x044,%0":: "r" (c));
	asm volatile ("csrr %0,0x044": "=r" (c)); // user interrupt pending
	res=c;

	// pmp configuration
	asm volatile ("csrr %0,0x3a0 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3a0,%0":: "r" (c));
	asm volatile ("csrr %0,0x3a0 ":"=r" (c));
	res=c;


	asm volatile ("csrr %0,0x3a1 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3a1,%0":: "r" (c));asm volatile ("csrr %0,0x3a1 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3a2 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3a2,%0":: "r" (c));asm volatile ("csrr %0,0x3a2 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3a3 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3a3,%0":: "r" (c));asm volatile ("csrr %0,0x3a3 ":"=r" (c));
	res=c;

	// pmp addresses
	asm volatile ("csrr %0,0x3b0 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b0,%0":: "r" (c));asm volatile ("csrr %0,0x3b0 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b1 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b1,%0":: "r" (c));asm volatile ("csrr %0,0x3b1 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b2 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b2,%0":: "r" (c));asm volatile ("csrr %0,0x3b2 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b3 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b3,%0":: "r" (c));asm volatile ("csrr %0,0x3b3 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b4 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b4,%0":: "r" (c));asm volatile ("csrr %0,0x3b4 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b5 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b5,%0":: "r" (c));asm volatile ("csrr %0,0x3b5 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b6 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b6,%0":: "r" (c));asm volatile ("csrr %0,0x3b6 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b7 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b7,%0":: "r" (c));asm volatile ("csrr %0,0x3b7 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b8 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b8,%0":: "r" (c));asm volatile ("csrr %0,0x3b8 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3b9 ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3b9,%0":: "r" (c));asm volatile ("csrr %0,0x3b9 ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3ba ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3ba,%0":: "r" (c));asm volatile ("csrr %0,0x3ba ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3bb ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3bb,%0":: "r" (c));asm volatile ("csrr %0,0x3bb ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3bc ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3bc,%0":: "r" (c));asm volatile ("csrr %0,0x3bc ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3bd ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3bd,%0":: "r" (c));asm volatile ("csrr %0,0x3bd ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3be ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3be,%0":: "r" (c));asm volatile ("csrr %0,0x3be ":"=r" (c));
	res=c;

	asm volatile ("csrr %0,0x3bf ":"=r" (c));
	res=c;
	asm volatile ("csrw 0x3bf,%0":: "r" (c));asm volatile ("csrr %0,0x3bf ":"=r" (c));
	res=c;
	// hardware loop csr
	asm volatile ("csrr %0, 0x7C0" : "=r" (c) );
	res=c;
	asm volatile ("csrw 0x7C0, %0" :: "r" (c) );
	asm volatile ("csrr %0, 0x7C0" : "=r" (c) );
	res=c;


	asm volatile ("csrr %0, 0x7C1" : "=r" (c) );
	res=c;
	asm volatile ("csrw 0x7C1, %0" :: "r" (c) );
	asm volatile ("csrr %0, 0x7C1" : "=r" (c) );
	res=c;

	asm volatile ("csrr %0, 0x7C2" : "=r" (c) );
	res=c;
	asm volatile ("csrw 0x7C2, %0" :: "r" (c) );
	asm volatile ("csrr %0, 0x7C2" : "=r" (c) );
	res=c;

	asm volatile ("csrr %0, 0x7C4" : "=r" (c) );
	res=c;
	asm volatile ("csrw 0x7C4, %0" :: "r" (c) );
	asm volatile ("csrr %0, 0x7C4" : "=r" (c) );
	res=c;

	asm volatile ("csrr %0, 0x7C5" : "=r" (c) );
	res=c;
	asm volatile ("csrw 0x7C5, %0" :: "r" (c) );
	asm volatile ("csrr %0, 0x7C5" : "=r" (c) );
	res=c;

	asm volatile ("csrr %0, 0x7C6" : "=r" (c) );
	res=c;
	asm volatile ("csrw 0x7C6, %0" :: "r" (0xbabbabab) );
	asm volatile ("csrr %0, 0x7C6" : "=r" (c) );
	res=c;

	// performancae counters
	asm volatile ("csrr %0,0x7a0": "=r" (c));// performance counter enable
	res=c;
	asm volatile ("csrw 0x7a0,%0":: "r" (c));asm volatile ("csrr %0,0x7a0": "=r" (c));// performance counter enable
	res=c;

	asm volatile("csrr %0,0x7a1 ": "=r" (c));	// performance counter mode
	res=c;
	asm volatile("csrw 0x7a1, %0":: "r" (c));asm volatile("csrr %0,0x7a1 ": "=r" (c));	// performance counter mode
	res=c;

	// perf counters from 0x780-0x79F
	asm volatile("csrr %0,0x780 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x780, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x780 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x780, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x780 ": "=r" (c));
	res=c;

	asm volatile("csrr %0,0x781 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x781, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x781 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x781, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x781 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x782 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x782, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x782 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x782, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x782 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x783 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x783, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x783 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x783, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x783 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x784 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x784, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x784 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x784, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x784 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x785 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x785, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x785 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x785, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x785 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x786 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x786, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x786 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x786, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x786 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x787 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x787, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x787 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x787, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x787 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x788 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x788, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x788 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x788, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x788 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x789 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x789, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x789 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x789, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x789 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x78A ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78A, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x78A ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78A, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x78A ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x78B ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78B, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x78B ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78B, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x78B ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x78C ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78C, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x78C ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78C, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x78C ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x78D ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78D, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x78D ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78D, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x78D ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x78E ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78E, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x78E ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78E, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x78E ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x78F ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78F, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x78F ": "=r" (c));
	res=c;
	asm volatile("csrw 0x78F, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x78F ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x790 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x790, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x790 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x790, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x790 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x791 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x791, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x791 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x791, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x791 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x792 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x792, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x792 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x792, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x792 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x793 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x793, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x793 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x793, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x793 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x794 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x794, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x794 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x794, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x794 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x795 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x795, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x795 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x795, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x795 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x796 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x796, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x796 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x796, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x796 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x797 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x797, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x797 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x797, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x797 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x798 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x798, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x798 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x798, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x798 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x799 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x799, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x799 ": "=r" (c));
	res=c;
	asm volatile("csrw 0x799, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x799 ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x79A ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79A, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x79A ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79A, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x79A ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x79B ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79B, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x79B ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79B, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x79B ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x79C ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79C, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x79C ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79C, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x79C ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x79D ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79D, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x79D ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79D, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x79D ": "=r" (c));
	res=c;


	asm volatile("csrr %0,0x79E ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79E, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x79E ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79E, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x79E ": "=r" (c));
	res=c;



	asm volatile("csrr %0,0x79F ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79F, %0":: "i" (0xFFFFFFFF));
	asm volatile("csrr %0,0x79F ": "=r" (c));
	res=c;
	asm volatile("csrw 0x79F, %0":: "i" (0x00000000));
	asm volatile("csrr %0,0x79F ": "=r" (c));
	res=c;

	int dummy_vector[100];
	int dummy_vector_2[100];

	// initialize data structure
	for(i=0;i<100;i++) {
		dummy_vector[i]=i;
		dummy_vector_2[i]=i;
	}

	// load and store instructions (pulp extension)
	//Register-Immediate Loads with Post-Increment
	b=dummy_vector;
	asm volatile ("p.lb %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sb %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	b=dummy_vector;
	asm volatile ("p.lbu %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sb %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	b=dummy_vector;
	asm volatile ("p.lh %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sh %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	b=dummy_vector;
	asm volatile ("p.lhu %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sh %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	b=dummy_vector;
	asm volatile ("p.lw %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sw %0,%1(%2!)": "=r" (c): "i" (0x4), "r" (b));
	//Register-Register Loads with Post-Increment
	b=0;
	asm volatile ("p.lb %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sb %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	b=0;
	asm volatile ("p.lbu %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sb %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	b=0;
	asm volatile ("p.lh %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sh %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	b=0;
	asm volatile ("p.lhu %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sh %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	b=0;
	asm volatile ("p.lw %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sw %0,%1(%2!)": "=r" (c): "r" (dummy_vector), "r" (b));
	//Register-Register Loads
	b=0;
	asm volatile ("p.lb %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sb %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));

	asm volatile ("p.lbu %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sb %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));

	asm volatile ("p.lh %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sh %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));

	asm volatile ("p.lhu %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sh %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));

	asm volatile ("p.lw %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));
	asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
	asm volatile ("p.sw %0,%1(%2)": "=r" (c): "r" (dummy_vector), "r" (b));

	// jump unconditional instruction
	asm volatile ("j here_we_go\n\there_we_go:");
	// nope
	asm volatile("nop");// converted into  addi x0,x0,0
	//////////////////////////////////////////////////
	//////////// TESTING REST OF CORE /////////////////
	///////////////////////////////////////////////////
#if TEST_CORE
	//-----------------------------------------------------------------
	// Check HWLOOP with lp.starti/lp.endi/lp.count
	//-----------------------------------------------------------------
	// RVC -> compressed instructions
	// no RVC
	i = 0;
	int  j = 0;
	int tmp=3;
	int tmp2=2;
	asm volatile (
			".option norvc;"
			"lp.count x0, %[N];"
			"lp.endi x0, end44;"
			"lp.starti x0, start44;"
			"start44: addi %[i], %[i], 1;"
			"end44: addi %[j], %[j], 10;"
			: [i] "+r" (i), [j] "+r" (j)
			: [N] "r" (5)
		     );
	// 2 then 4 byte instruction combo
	i = 0; j = 0;
	asm volatile (
			".option norvc;"
			// save a0
			"mv %[tmp], a0;"
			"li a0, 0;"
			// loop
			"lp.count x0, %[N];"
			"lp.endi x0, end24;"
			"lp.starti x0, start24;"
			".option rvc;"
			"start24: c.addi a0, 1;"
			".option norvc;"
			"end24: addi %[j], %[j], 10;"
			// restore a0
			"mv %[i], a0;"
			"mv a0, %[tmp];"
			: [i] "+r" (i), [j] "+r" (j), [tmp] "+r" (tmp)
			: [N] "r" (10)
			: "a0"
		     );
	// 4 then 2 byte instruction combo
	i = 0; j = 0;
	asm volatile (
			".option norvc;"
			// save a0
			"mv %[tmp], a0;"
			"li a0, 0;"
			// loop
			"lp.count x0, %[N];"
			"lp.endi x0, end42;"
			"lp.starti x0, start42;"
			"start42: addi %[i], %[i], 1;"
			".option rvc;"
			"end42: c.addi a0, 10;"
			".option norvc;"
			// restore a0
			"mv %[j], a0;"
			"mv a0, %[tmp];"
			: [i] "+r" (i), [j] "+r" (j), [tmp] "+r" (tmp)
			: [N] "r" (10)
			: "a0"
		     );
	// RVC only
	i = 0; j = 0;
	asm volatile (
			".option norvc;"
			// save a0, a1
			"mv %[tmp], a0;"
			"mv %[tmp_2], a1;"
			"li a0, 0;"
			"li a1, 0;"
			// loop
			"lp.count x0, %[N];"
			"lp.endi x0, end22;"
			"lp.starti x0, start22;"
			".option rvc;"
			"start22: c.addi a0, 1;"
			"end22: c.addi a1, 10;"
			".option norvc;"
			// restore a0, a1
			"mv %[i], a0;"
			"mv %[j], a1;"
			"mv a0, %[tmp];"
			"mv a1, %[tmp_2];"
			: [i] "+r" (i), [j] "+r" (j), [tmp] "+r" (tmp), [tmp_2] "+r" (tmp2)
			: [N] "r" (10)
			   : "a0", "a1"
				   );

	//-----------------------------------------------------------------
	// Check HWLOOP with lp.setup
	//-----------------------------------------------------------------
	i = 0; j = 0;
	asm volatile (
			".option norvc;"
			"lp.setup x0, %[N], endstp;"
			"addi %[i], %[i], 1;"
			"endstp: addi %[j], %[j], 10;"
			: [i] "+r" (i), [j] "+r" (j)
			: [N] "r" (10)
		     );

	//-----------------------------------------------------------------
	// Check HWLOOP with lp.starti/lp.endi/lp.count and same endpoint
	//-----------------------------------------------------------------

	// no RVC
	i = 0; j = 0;
	asm volatile (
			".option norvc;"
			"lp.count  x1, %[N];"
			"lp.endi   x1, endE;"
			"lp.starti x1, startE;"
			"startE: lp.count  x0, %[N];"
			"lp.endi   x0, endI;"
			"lp.starti x0, startI;"
			"startI: addi %[i], %[i], 1;"
			"endE: endI:   addi %[j], %[j], 10;"
			: [i] "+r" (i), [j] "+r" (j)
			: [N] "r" (10)
		     );
	// write in a forbidden register
	register int dummy_reg asm ("x0");
	res=dummy_reg;
	dummy_reg=res;
	// writig in all intger registers
	register int x1 asm ("x1");
	x1=0xFFFFFFFF;
	res=x1;
	x1=0x00000000;
	res=x1;

	register int x2 asm ("x2");
	x2=0xFFFFFFFF;
	res=x2;
	x2=0x00000000;
	res=x2;


	register int x3 asm ("x3");
	x3=0xFFFFFFFF;
	res=x3;
	x3=0x00000000;
	res=x3;


	register int x4 asm ("x4");
	x4=0xFFFFFFFF;
	res=x4;
	x4=0x00000000;
	res=x4;


	register int x5 asm ("x5");
	x5=0xFFFFFFFF;
	res=x5;
	x5=0x00000000;
	res=x5;


	register int x6 asm ("x6");
	x6=0xFFFFFFFF;
	res=x6;
	x6=0x00000000;
	res=x6;


	register int x7 asm ("x7");
	x7=0xFFFFFFFF;
	res=x7;
	x7=0x00000000;
	res=x7;


	register int x8 asm ("x8");
	x8=0xFFFFFFFF;
	res=x8;
	x8=0x00000000;
	res=x8;


	register int x9 asm ("x9");
	x9=0xFFFFFFFF;
	res=x9;
	x9=0x00000000;
	res=x9;


	register int x10 asm ("x10");
	x10=0xFFFFFFFF;
	res=x10;
	x10=0x00000000;
	res=x10;


	register int x12 asm ("x12");
	x12=0xFFFFFFFF;
	res=x12;
	x12=0x00000000;
	res=x12;


	register int x13 asm ("x13");
	x13 0xFFFFFFFF;
	res=x13
		x13 0x00000000;
	res=x13


		register int x14 asm ("x14");
	x14=0xFFFFFFFF;
	res=x14;
	x14=0x00000000;
	res=x14;


	register int x15 asm ("x15");
	x15=0xFFFFFFFF;
	res=x15;
	x15=0x00000000;
	res=x15;


	register int x16 asm ("x16");
	x16=0xFFFFFFFF;
	res=x16;
	x16=0x00000000;
	res=x16;


	register int x17 asm ("x17");
	x17=0xFFFFFFFF;
	res=x17;
	x17=0x00000000;
	res=x17;


	register int x18 asm ("x18");
	x18=0xFFFFFFFF;
	res=x18;
	x18=0x00000000;
	res=x18;


	register int x19 asm ("x19");
	x19=0xFFFFFFFF;
	res=x19;
	x19=0x00000000;
	res=x19;


	register int x20 asm ("x20");
	x20=0xFFFFFFFF;
	res=x20;
	x20=0x00000000;
	res=x20;


	register int x21 asm ("x21");
	x21 =0xFFFFFFFF;
	res=x21
		x21 =0x00000000;
	res=x21


		register int x22 asm ("x22");
	x22=0xFFFFFFFF;
	res=x22;
	x22=0x00000000;
	res=x22;


	register int x23 asm ("x23");
	x23=0xFFFFFFFF;
	res=x23;
	x23=0x00000000;
	res=x23;


	register int x24 asm ("x24");
	x24=0xFFFFFFFF;
	res=x24;
	x24=0x00000000;
	res=x24;


	register int x25 asm ("x25");
	x25=0xFFFFFFFF;
	res=x25;
	x25=0x00000000;
	res=x25;


	register int x26 asm ("x26");
	x26=0xFFFFFFFF;
	res=x26;
	x26=0x00000000;
	res=x26;


	register int x27 asm ("x27");
	x27=0xFFFFFFFF;
	res=x27;
	x27=0x00000000;
	res=x27;


	register int x28 asm ("x28");
	x28=0xFFFFFFFF;
	res=x28;
	x28=0x00000000;
	res=x28;


	register int x29 asm ("x29");
	x29=0xFFFFFFFF;
	res=x29;
	x29=0x00000000;
	res=x29;


	register int x30 asm ("x30");
	x30=0xFFFFFFFF;
	res=x30;
	x30=0x00000000;
	res=x30;


	register int x31 asm ("x31");
	x31=0xFFFFFFFF;
	res=x31;
	x31=0x00000000;
	res=x31;



	asm volatile ("li %0,%1": "=r" (c): "i" (0x3245));
	res=c;
	a=c;
	asm volatile ("mv %0,%1":"=r" (c): "r" (a));
	res=c;
	a=c;
	asm volatile ("auipc %0,%1": "=r" (c): "n" (0x000FF));
	res=c;
	a=c;
	asm volatile ("lui %0,%1": "=r" (c): "n" (0x000FF));
	res=c;
	a=c;
	// hint instructions
	asm volatile ("lui x0,%0": : "i" (0x000ff));
	asm volatile ("auipc x0,%0":: "i" (0x000ff));
	asm volatile ("andi x0,%0,%1"::"r" (a), "i" (0x000ff));
	asm volatile ("ori x0,%0,%1":: "r" (a),"i" (0x000ff));
	asm volatile ("xori x0,%0,%1"::"r" (a), "i" (0x000ff));
	asm volatile ("add x0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("sub x0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("and x0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("or x0,%0,%1"::"r" (a), "r" (b));
	asm volatile ("xor x0,%0,%1"::"r" (a), "r" (b));

	// enviromental call and breakpoints from risc v manual
	asm volatile ( "slli x0, x0, 0x1f # Entry NOP"
			"ebreak # Break to debugger"
			"srai x0, x0, 7 # NOP encoding the semihosting call number 7");

	// synchromize i/o and memory operations
	asm volatile ("fence.I"); // inputs
	asm volatile ("fence.O"); // outputs
	asm volatile ("fence.R"); // memory reads
	asm volatile ("fence.W"); // memory write
	asm volatile ("fence %0":: "i" (1));
	asm volatile ("fence %0":: "i" (0));
	asm volatile ("fence.tso");
	// atomic memory operations
	/*	asm volatile ("amoswap.w %0,%1,(%2) ": "=r" (c): "r" (a), "r" (pattern[3]) );
		res=c;
		asm volatile ("amoadd.w.rl %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[3]) );
		res=c;
		asm volatile ("amoand.w.aq %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[20]) );
		res=c;
		asm volatile ("amoor.w.rl %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[15]) );
		res=c;
		asm volatile ("amoxor.w.aq %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[3]) );
		res=c;
		asm volatile ("amomax.w.rl %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[8]) );
		res=c;
		asm volatile ("amomaxu.w.aq %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[3]) );
		res=c;
		asm volatile ("amomin.w.rl %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[0]) );
		res=c;
		asm volatile ("amominu.w.aq %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[3]) );
		res=c;
		asm volatile ("amominu.w.rl %0,%1,%2 ": "=r" (c): "r" (a), "o" (pattern[3]) );
		res=c;
		*/
	asm volatile ("li t0, 1 # Initialize swap value."
			"again:"
			"amoswap.w.aq t0, t0, (a0) # Attempt to acquire lock."
			"			bnez t0, again # Retry if held."
			"# Critical section."
			"	addi %0,%0,1"
			"amoswap.w.rl x0, x0, (a0) # Release lock by storing 0.": "=r" (c));
	res=c;
	// access to dummy vector increasing the stall due to cache miss
	int index=0;
	int dummy=0;
	for (i=0;i<100;i++){
		index=dummy_vector_2[i];
		dummy+=dummy_vector[index];
	}
	// misalligned accesses from official tests of pulpino

	volatile char word[8]= { 0,1,2,3,4,5,6,7};
	uint32_t act;

	asm volatile ("lw %0, 1(%1)"
			: "+r" (c)
			: "r" (word));

	asm volatile ("lw %0, 2(%1)"
			:  "+r" (c)
			: "r" (word));


	asm volatile ("lw %0, 3(%1)"
			:  "+r" (act)
			:  "r" (word));

	asm volatile ("lhu %0, 1(%1)"
			:  "+r" (c)
			: "r" (word));


	asm volatile ("lhu %0, 2(%1)"
			:  "+r" (c)
			: "r" (word));


	asm volatile ("lhu %0, 3(%1)\n"
			:  "+r" (c)
			:  "r" (word));


	// sign extension
	word[0] = 0x80;
	word[1] = 0x81;
	word[2] = 0x82;
	word[3] = 0x83;
	word[4] = 0x84;
	word[5] = 0x85;
	word[6] = 0x86;
	word[7] = 0x87;

	asm volatile ("lh %0, 1(%1)"
			:  "+r" (c)
			: "r" (word));


	asm volatile ("lh %0, 2(%1)"
			: "+r" (c)
			:  "r" (word));


	asm volatile ("lh %0, 3(%1)"
			:  "+r" (c)
			: "r" (word));



	volatile char val[8];
	uint32_t word_2;

	for(i = 0; i < 8; i++) val[i] = 0;
	word_2 = 0x01020304;
	asm volatile ("sw %[a], 1(%[addr])\n"
			: : [addr] "r" (val), [a] "r" (word_2));

	for(i = 0; i < 8; i++) val[i] = 0;
	word_2 = 0x01020304;
	asm volatile ("sw %[a], 2(%[addr])\n"
			: : [addr] "r" (val), [a] "r" (word_2));

	for(i = 0; i < 8; i++) val[i] = 0;
	word_2 = 0x01020304;
	asm volatile ("sw %[a], 3(%[addr])\n"
			: : [addr] "r" (val), [a] "r" (word_2));

	for(i = 0; i < 8; i++) val[i] = 0;
	word_2 = 0x0304;
	asm volatile ("sh %[a], 1(%[addr])\n"
			: : [addr] "r" (val), [a] "r" (word_2));



	for(i = 0; i < 8; i++) val[i] = 0;
	word_2 = 0x0304;
	asm volatile ("sh %[a], 2(%[addr])\n"
			: : [addr] "r" (val), [a] "r" (word_2));



	for(i = 0; i < 8; i++) val[i] = 0;
	word_2 = 0x0304;
	asm volatile ("sh %[a], 3(%[addr])\n"
			: : [addr] "r" (val), [a] "r" (word_2));

	//load and store conditional ops ( from risc v spec )
	asm volatile ("# a0 holds address of memory location"
			"# a1 holds expected value"
			"# a2 holds desired value"
			"# a0 holds return value, 0 if successful, !0 otherwise"
			"cas:"
			"lr.w t0, %0 # Load original value."
			"			bne t0, a1, fail # Doesn’t match, so fail."
			"			sc.w t0, a2, %0 # Try to update."
			"			bnez t0, cas # Retry if store-conditional failed."
			"			fail:": : "r" (c));
	res=c;
	// normal  loops
	int dummy_2=0;
	for(int k=0;k<3;k++) {
		for(int j=0;j<3;j++) {
			dummy++;
			dummy_2++;
		}
	}
	// pmp
	int error = 0;
	int failed = 0;

	for(int i=0;i<64;i++)
		protected_data[i] = 0;

	// Check if the PMP can prevent X, R and W from protected regions
	error = check_xrw_tor();

	if(error != 0)
		printf("TEST XRW FAILED :( - errors %d \n", error);
	else
		printf("TEST XRW OK :)\n" );

	failed+=error;

	error = check_special_case();

	if(error != 0)
		printf("TEST SPECIAL FAILED :( - errors %d \n", error);
	else
		printf("TEST SPECIAL OK :)\n" );

	failed+=error;

	// Check if writing to Machine CSRs or executing Machine instructions is causing exceptions
	error = check_user_exceptions();

	if(error != 0)
		printf("TEST USER EXCEPTIONS FAILED :( - errors %d \n", error);
	else
		printf("TEST USER EXCEPTIONS OK :)\n" );

	failed+=error;
	// filling and generating the ivt TODO

	// ecall and ret + saving regs on stack
	f1();
#endif
	return EXIT_SUCCESS;
}


#if TEST_CORE

// checking the subroutins calls and returns
void __attribute__((noinline))  f1(void ) {
	f2();
	return;
}

void  __attribute__((noinline)) f2(void) {
	f3();
	int test=f4(1);
	return;
}
void   __attribute__((noinline)) f3(void){
	asm volatile("nop");
	return;
}

int __attribute__((noinline)) f4(int par) {
	return (par++)>>1;
}

void __attribute__((aligned)) task_user()
{
	unsigned int A = 0;

	for(int i=0;i<64;i++)
		protected_data[i] = i;

	for(int i=0;i<64;i++)
		A+=protected_data[i];

	asm volatile("ecall");

}
void __attribute__((aligned)) task_user_exeption()
{
	asm volatile(".word 0x00007123;");
	asm volatile("csrrw x0, mepc, x15");

}

void __attribute__((interrupt)) __perturbation_handler()
{

}
void __attribute__((inline)) my_exception()
{
	asm volatile(
			"lw x15, 0x0(%[return_addr])\n"
			"csrrw x0, mepc, x15\n"
			"csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
			: : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");
}

void __attribute__((inline)) my_dataerr_handler()
{
	asm volatile(
			"lw x15, 0x0(%[return_addr])\n"
			"csrrw x0, mepc, x15\n"
			"csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
			: : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");

}

void __attribute__((interrupt)) __test_exceptions_handler()
{

	unsigned int mcause;
	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

	switch(mcause)
	{

		case INSTR_ACC_FAULT:
			//	my_dataerr_handler();
			asm volatile(
					"lw x15, 0x0(%[return_addr])\n"
					"csrrw x0, mepc, x15\n"
					"csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
					: : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");


			break;
		case LOAD_ACC_FAULT:
			//		my_dataerr_handler();
			asm volatile(
					"lw x15, 0x0(%[return_addr])\n"
					"csrrw x0, mepc, x15\n"
					"csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
					: : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");


			break;
		case STORE_ACC_FAULT:
			//			my_dataerr_handler();
			asm volatile(
					"lw x15, 0x0(%[return_addr])\n"
					"csrrw x0, mepc, x15\n"
					"csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
					: : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");


			break;
		case ECALL_UCAUSE:
			//		my_exception();
			asm volatile(
					"lw x15, 0x0(%[return_addr])\n"
					"csrrw x0, mepc, x15\n"
					"csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
					: : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");

		case ILLEGAL_INSTR:
			asm volatile(
					"lw x15, 0x0(%[return_addr])\n"
					"csrrw x0, mepc, x15\n"
					"csrrs x0, mstatus, %[mpp_machine]\n" //go back to M mode
					: : [return_addr] "r" (&return_here_instr), [mpp_machine] "r" (0x1800) : "x15");
			//	my_exception();
			break;
	}

	//go back to M mode
	asm volatile (
			"csrrw x0, mstatus, %[mpp_user]\n"
			:  : [mpp_user] "r" (0x1800));

}


//================================================================
// Check XRW permission with 1 Region using the TOR mode
//================================================================
int check_xrw_tor(void) {

	unsigned int i;
	unsigned int error = 0;

	unsigned int lower_bound_data = protected_data;
	unsigned int upper_bound_data = lower_bound_data + 64;

	unsigned int lower_bound_instr = task_user;
	unsigned int upper_bound_instr = task_user + 64;


	volatile int mcause = 0;

	unsigned int debug_addr = 0x1A110000;

	unsigned int pert_addr  = debug_addr | 0x600;

	unsigned int pert_instr_stall_mode_addr  = pert_addr | 0x10;
	unsigned int pert_instr_maxstall         = pert_addr | 0x14;
	unsigned int pert_instr_grant_stall      = pert_addr | 0x18;
	unsigned int pert_instr_valid_stall      = pert_addr | 0x1C;

	unsigned int pert_data_stall_mode_addr   = pert_addr | 0x0;
	unsigned int pert_data_maxstall          = pert_addr | 0x4;
	unsigned int pert_data_grant_stall       = pert_addr | 0x8;
	unsigned int pert_data_valid_stall       = pert_addr | 0xC;


	unsigned int pert_irq_mode_addr          = pert_addr | 0x20;
	unsigned int pert_irq_min_cycles         = pert_addr | 0x24;
	unsigned int pert_irq_max_cycles         = pert_addr | 0x28;
	unsigned int pert_irq_min_id             = pert_addr | 0x2C;
	unsigned int pert_irq_max_id             = pert_addr | 0x30;
	unsigned int pert_irq_resp_is            = pert_addr | 0x34;
	unsigned int pert_irq_valid_stall        = pert_addr | 0x38;



	lower_bound_data = lower_bound_data >> 2;
	upper_bound_data = upper_bound_data >> 2;

	lower_bound_instr = lower_bound_instr >> 2;
	upper_bound_instr = upper_bound_instr >> 2;

	int irq = rt_irq_disable();

#ifdef PERTURBATION_INSTR
	//set random stalls on Instruction Fetch Interface
	asm volatile ("set_random_stall_instr:"
			"sw %[maxstall], 0x(%[pert_instr_maxstall])\n"
			"sw %[random_mode], 0x(%[pert_instr_stall_mode_addr])\n" : : [maxstall] "r" (4), [random_mode] "r" (2), \
			[pert_instr_maxstall] "r" (pert_instr_maxstall), \
			[pert_instr_stall_mode_addr] "r" (pert_instr_stall_mode_addr));
#endif

#ifdef PERTURBATION_DATA
	//set random stalls on Data Interface
	asm volatile ("set_random_stall_data:"
			"sw %[maxstall], 0x(%[pert_data_maxstall])\n"
			"sw %[random_mode], 0x(%[pert_data_stall_mode_addr])\n" : : [maxstall] "r" (4), [random_mode] "r" (2), \
			[pert_data_maxstall] "r" (pert_data_maxstall), \
			[pert_data_stall_mode_addr] "r" (pert_data_stall_mode_addr));
#endif


	//putting in the ivt
	vector_table[0]= __test_exceptions_handler;

	//give to every entry all the accesses but addr1
	asm volatile (
			"csrrw x0, mtvec, %[bootaddr]\n"

			"la x14, return_here_1\n"
			"sw x14, 0(%[return_addr])\n"

			//NO X in REGION 4 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"csrrw x0, 0x3A1, %[pmpcfg1]\n"
			"csrrw x0, 0x3A2, %[pmpcfg2]\n"
			"csrrw x0, 0x3A3, %[pmpcfg3]\n"

			"csrrw x0, 0x3B0, %[pmpaddr0]\n"
			"csrrw x0, 0x3B1, %[pmpaddr1]\n"
			"csrrw x0, 0x3B2, %[pmpaddr2]\n"
			"csrrw x0, 0x3B3, %[pmpaddr3]\n"

			"csrrw x0, 0x3B4, %[pmpaddr4]\n"
			"csrrw x0, 0x3B5, %[pmpaddr5]\n"
			"csrrw x0, 0x3B6, %[pmpaddr6]\n"
			"csrrw x0, 0x3B7, %[pmpaddr7]\n"

			"csrrw x0, 0x3B8, %[pmpaddr8]\n"
			"csrrw x0, 0x3B9, %[pmpaddr9]\n"
			"csrrw x0, 0x3BA, %[pmpaddra]\n"
			"csrrw x0, 0x3BB, %[pmpaddrb]\n"

			"csrrw x0, 0x3BC, %[pmpaddrc]\n"
			"csrrw x0, 0x3BD, %[pmpaddrd]\n"
			"csrrw x0, 0x3BE, %[pmpaddre]\n"
			"csrrw x0, 0x3BF, %[pmpaddrf]\n"
			"mv x18, %[stack_data]\n"
			PUSH_ALL
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, %[mepc]\n"
			"mret\n"
			"return_here_1: \n"
			POP_ALL
			:  : [pmpcfg0] "r" (0x0B0F0F0F), [pmpcfg1] "r" (0x0F0F0F0F), [pmpcfg2] "r" (0x0F0F0F0F), [pmpcfg3] "r" (0x0F0F0F0F),
		[pmpaddr0] "r" (lower_bound_data), [pmpaddr1] "r" (upper_bound_data), [pmpaddr2] "r" (lower_bound_instr), [pmpaddr3] "r" (upper_bound_instr),
		[pmpaddr4] "r" (0xFFFFFFFF), [pmpaddr5] "r" (0xFFFFFFFF), [pmpaddr6] "r" (0xFFFFFFFF), [pmpaddr7] "r" (0xFFFFFFFF),
		[pmpaddr8] "r" (0xFFFFFFFF), [pmpaddr9] "r" (0xFFFFFFFF), [pmpaddra] "r" (0xFFFFFFFF), [pmpaddrb] "r" (0xFFFFFFFF),
		[pmpaddrc] "r" (0xFFFFFFFF), [pmpaddrd] "r" (0xFFFFFFFF), [pmpaddre] "r" (0xFFFFFFFF), [pmpaddrf] "r" (0xFFFFFFFF),
		[mepc] "r" (task_user), [bootaddr] "r" (0x1C008000), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x15", "x14", "x18");

	//in the main we initialized to 0, be sure they haven't been modified
	for(int i=0;i<64;i++) {
		if(protected_data[i] != 0)
			error++;
	}
	if (error != 0) printf("ERROR: X access failed\n");

	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

	if(mcause != INSTR_ACC_FAULT)
		error++;
	if (error != 0) printf("ERROR: X CAUSE failed\n");

	if (error != 0) return error;

	//in the main we initialized to 0, be sure they haven't been modified
	asm volatile (
			"la x14, return_here_2\n"
			"sw x14, 0(%[return_addr])\n"

			//NO W in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"mv x18, %[stack_data]\n"
			PUSH_ALL
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, %[mepc]\n"
			"mret\n"
			"return_here_2: \n"
			POP_ALL

			:  : [pmpcfg0] "r" (0x0F0F0D0F),
			[mepc] "r" (task_user), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x14", "x18");

	for(int i=0;i<64;i++) {
		if(protected_data[i] != 0)
			error++;
	}
	if (error != 0) printf("ERROR: W access failed\n");

	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
	if(mcause != STORE_ACC_FAULT)
		error++;
	if (error != 0) printf("ERROR: W CAUSE failed\n");

	if (error != 0) return error;


	asm volatile (
			"la x14, return_here_3\n"
			"sw x14, 0(%[return_addr])\n"

			//NO R in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"mv x18, %[stack_data]\n"
			PUSH_ALL
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, %[mepc]\n"
			"mret\n"
			"return_here_3: \n"
			POP_ALL

			:  : [pmpcfg0] "r" (0x0F0F0E0F),
			[mepc] "r" (task_user), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x14", "x18");

	for(int i=0;i<64;i++) {
		if(protected_data[i] != i)
			error++;
	}
	if (error != 0) printf("ERROR: R access failed\n");

	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
	if(mcause != LOAD_ACC_FAULT)
		error++;
	if (error != 0) printf("ERROR: R CAUSE failed\n");

	if (error != 0) return error;


	asm volatile (
			"la x14, return_here_4\n"
			"sw x14, 0(%[return_addr])\n"

			//Everything ok in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"la x1, return_here_4\n"
			"mv x18, %[stack_data]\n"
			PUSH_ALL
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, %[mepc]\n"
			"mret\n"
			"return_here_4: \n"
			POP_ALL

			:  : [pmpcfg0] "r" (0x0F0F0F0F),
			[mepc] "r" (task_user), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x14", "x18");

	for(int i=0;i<64;i++) {                                                                                                                                                                                               if(protected_data[i] != i)
		error++;
	}

#ifdef PERTURBATION_INSTR
	//set random stalls on Instruction Fetch Interface
	asm volatile (
			"sw x0, 0x(%[pert_instr_grant_stall])\n"
			"sw x0, 0x(%[pert_instr_valid_stall])\n"
			"sw %[random_mode], 0x(%[pert_instr_stall_mode_addr])\n" : : [pert_instr_grant_stall] "r" (0), [pert_instr_valid_stall] "r" (1), \
			[random_mode] "r" (1), \
			[pert_instr_stall_mode_addr] "r" (pert_instr_stall_mode_addr));
#endif

#ifdef PERTURBATION_DATA
	//set random stalls on Data Interface
	asm volatile (
			"sw x0, 0x(%[pert_data_grant_stall])\n"
			"sw x0, 0x(%[pert_data_valid_stall])\n"
			"sw %[random_mode], 0x(%[pert_data_stall_mode_addr])\n" : : [pert_data_grant_stall] "r" (0), [pert_data_valid_stall] "r" (1), \
			[random_mode] "r" (1), \
			[pert_data_stall_mode_addr] "r" (pert_data_stall_mode_addr));
#endif
	return error;

}


int check_special_case(void) {

	unsigned int i;
	unsigned int error = 0;

	unsigned int lower_bound_data = protected_data;
	unsigned int upper_bound_data = lower_bound_data + 64;

	unsigned int lower_bound_instr = task_user;
	unsigned int upper_bound_instr = task_user + 64;


	volatile int mcause = 0;

	unsigned int debug_addr = 0x1A110000;

	unsigned int pert_addr  = debug_addr | 0x600;

	unsigned int pert_instr_stall_mode_addr  = pert_addr | 0x10;
	unsigned int pert_instr_maxstall         = pert_addr | 0x14;
	unsigned int pert_instr_grant_stall      = pert_addr | 0x18;
	unsigned int pert_instr_valid_stall      = pert_addr | 0x1C;

	unsigned int pert_data_stall_mode_addr   = pert_addr | 0x0;
	unsigned int pert_data_maxstall          = pert_addr | 0x4;
	unsigned int pert_data_grant_stall       = pert_addr | 0x8;
	unsigned int pert_data_valid_stall       = pert_addr | 0xC;

	unsigned int pert_irq_mode_addr          = pert_addr | 0x20;
	unsigned int pert_irq_min_cycles         = pert_addr | 0x24;
	unsigned int pert_irq_max_cycles         = pert_addr | 0x28;
	unsigned int pert_irq_min_id             = pert_addr | 0x2C;
	unsigned int pert_irq_max_id             = pert_addr | 0x30;
	unsigned int pert_irq_resp_is            = pert_addr | 0x34;
	unsigned int pert_irq_pc_trig            = pert_addr | 0x38;


	lower_bound_data = lower_bound_data >> 2;
	upper_bound_data = upper_bound_data >> 2;

	lower_bound_instr = lower_bound_instr >> 2;
	upper_bound_instr = upper_bound_instr >> 2;

	int irq = rt_irq_disable();

	vector_table[0]=__test_exceptions_handler;

	int test_val      = 0xabbaabba;
	protected_data[0] = 0xdeadbeef;

	//give to every entry all the accesses but addr1
	asm volatile (
			"csrrw x0, mtvec, %[bootaddr]\n"
			:  : [bootaddr] "r" (0x1C008000) : "x15");

	asm volatile (
			"la x14, return_here_sc_1\n"
			"sw x14, 0(%[return_addr])\n"
			"mv x16, %[DEAD_VAL]\n"
			//NO W in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"la x14, user_mode_1\n"
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, x14\n"
			"mret\n"
			"user_mode_1: \n"
			"lw x16, 0(%[addr_prohibited])\n"
			"loop_1: jal x0, loop_1\n"
			//cycle0: load in EX sent address to PMP, JMP in ID is jumping
			//cycle1: data error arrives to the pipeline, now exception and return to return_here_sc_1
			"return_here_sc_1: nop\n"
			"mv %[check_val], x16\n"

			: [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
			[addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

	if(test_val == 0xdeadbeef){
		printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
		error++;
	}
	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
	if(mcause != LOAD_ACC_FAULT)
		error++;



	test_val = 0xabbaabba;
	protected_data[0] = 0xdeadbeef;

	asm volatile (
			"la x14, return_here_sc_2\n"
			"sw x14, 0(%[return_addr])\n"
			"mv x16, %[DEAD_VAL]\n"
			//NO W in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"la x14, user_mode_2\n"
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, x14\n"
			"mret\n"
			"user_mode_2: \n"
			"lw x16, 0(%[addr_prohibited])\n"
			"csrrs x0, 0x041, x0\n"
			//cycle0: load in EX sent address to PMP, CSR in ID is moving the PIPELINE at the next STATE
			//cycle1: data error arrives and exception and return to return_here_sc_2
			"return_here_sc_2: nop\n"
			"mv %[check_val], x16\n"

			: [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
			[addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

	if(test_val == 0xdeadbeef){
		printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
		error++;
	}
	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
	if(mcause != LOAD_ACC_FAULT)
		error++;


	test_val = 0xabbaabba;
	protected_data[0] = 0xdeadbeef;
	asm volatile (
			"la x14, return_here_sc_3\n"
			"sw x14, 0(%[return_addr])\n"
			"mv x16, %[DEAD_VAL]\n"
			//NO W in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"la x14, user_mode_3\n"
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, x14\n"
			"mret\n"
			"user_mode_3: \n"
			"lw x16, 0(%[addr_prohibited])\n"
			"csrrs x0, 0x300, x0\n" //--> access to MSTATUS cause illegal in U mode
			//cycle0: load in EX sent address to PMP, illegal in ID is moving the PIPELINE at the next STATE
			//cycle1: data error arrives and exception and return to return_here_sc_3
			"return_here_sc_3: nop\n"
			"mv %[check_val], x16\n"

			: [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
			[addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

	if(test_val == 0xdeadbeef){
		printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
		error++;
	}
	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
	if(mcause != LOAD_ACC_FAULT)
		error++;

	test_val = 0xabbaabba;
	protected_data[0] = 0xdeadbeef;
	asm volatile (
			"la x14, return_here_sc_4\n"
			"sw x14, 0(%[return_addr])\n"
			"mv x16, %[DEAD_VAL]\n"
			//NO W in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"la x14, user_mode_4\n"
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, x14\n"
			"mret\n"
			"user_mode_4: \n"
			"lw x16, 0(%[addr_prohibited])\n"
			"ecall\n"
			//cycle0: load in EX sent address to PMP, ecall in ID is moving the PIPELINE at the next STATE
			//cycle1: data error arrives and exception and return to return_here_sc_4
			"return_here_sc_4: nop\n"
			"mv %[check_val], x16\n"

			: [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr),
			[addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

	if(test_val == 0xdeadbeef){
		printf("Error! test_val is %x, expected %x\n", test_val, 0xabbaabba);
		error++;
	}
	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));
	if(mcause != LOAD_ACC_FAULT)
		error++;


#ifdef PERTURBATION_ITC
	*((unsigned int *)pert_irq_mode_addr) = 3; //PC TRIG MODE
	vector_table[18]= __perturbation_handler; //perturbation IRQ is 0x12

	test_val = 0xabbaabba;
	asm volatile (
			"csrrs x0, 0x300, 0x8\n"
			"la x14, return_here_sc_5\n"
			"sw x14, 0(%[return_addr])\n"
			"mv x16, %[DEAD_VAL]\n"
			//NO W in REGION 1 - TOR
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"la x14, stop_instr_5\n"
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, x14\n"
			"la x14, stop_instr_5\n"
			"sw x14, 0(%[pert_irq_pc_trig])\n"
			"mret\n"
			"stop_instr_5: lw x16, 0(%[addr_prohibited])\n"
			"nop\n" //this instruction will be interrupted as the INT_REQ is registered
			//cycle0: load in EX sent address to PMP, IRQ in ID is moving the PIPELINE at the next STATE
			//cycle1: data error arrives and exception and return to return_here_sc_5
			"return_here_sc_5: nop\n"
			"mv %[check_val], x16\n"
			: [check_val] "=r" (test_val) : [pmpcfg0] "r" (0x0F0F0E0F), [return_addr] "r" (&return_here_instr), [pert_irq_pc_trig] "r" (pert_irq_pc_trig),
			[addr_prohibited] "r" (protected_data), [DEAD_VAL] "r" (0xdead), [mpp_user] "r" (0) : "x14", "x16");

	if(test_val != 0xDEAD){
		printf("Error! test_val is %x\n", test_val);
		error++;
	}

#endif

	return error;

}


//================================================================
// Check USER Exceptions
//================================================================
int check_user_exceptions(void) {

	unsigned int i;
	unsigned int error = 0;
	volatile int mcause = 0;


	int irq = rt_irq_disable();

	vector_table	[0]=__test_exceptions_handler;


	asm volatile (
			"csrrw x0, mtvec, %[bootaddr]\n"

			"la x14, return_here_illegal\n"
			"sw x14, 0(%[return_addr])\n"

			//NO restrictions for USER
			"csrrw x0, 0x3A0, %[pmpcfg0]\n"
			"csrrw x0, 0x3A1, %[pmpcfg1]\n"
			"csrrw x0, 0x3A2, %[pmpcfg2]\n"
			"csrrw x0, 0x3A3, %[pmpcfg3]\n"

			"csrrw x0, 0x3B0, %[pmpaddr0]\n"
			"csrrw x0, 0x3B1, %[pmpaddr1]\n"
			"csrrw x0, 0x3B2, %[pmpaddr2]\n"
			"csrrw x0, 0x3B3, %[pmpaddr3]\n"

			"csrrw x0, 0x3B4, %[pmpaddr4]\n"
			"csrrw x0, 0x3B5, %[pmpaddr5]\n"
			"csrrw x0, 0x3B6, %[pmpaddr6]\n"
			"csrrw x0, 0x3B7, %[pmpaddr7]\n"

			"csrrw x0, 0x3B8, %[pmpaddr8]\n"
			"csrrw x0, 0x3B9, %[pmpaddr9]\n"
			"csrrw x0, 0x3BA, %[pmpaddra]\n"
			"csrrw x0, 0x3BB, %[pmpaddrb]\n"

			"csrrw x0, 0x3BC, %[pmpaddrc]\n"
			"csrrw x0, 0x3BD, %[pmpaddrd]\n"
			"csrrw x0, 0x3BE, %[pmpaddre]\n"
			"csrrw x0, 0x3BF, %[pmpaddrf]\n"
			"mv x18, %[stack_data]\n"
			PUSH_ALL
			"csrrw x0, mstatus, %[mpp_user]\n"
			"csrrw x0, mepc, %[mepc]\n"
			"mret\n"
			"return_here_illegal: \n"
			POP_ALL
			:  : [pmpcfg0] "r" (0x0F0F0F0F), [pmpcfg1] "r" (0x0F0F0F0F), [pmpcfg2] "r" (0x0F0F0F0F), [pmpcfg3] "r" (0x0F0F0F0F),
		[pmpaddr0] "r" (0xFFFFFFFF), [pmpaddr1] "r" (0xFFFFFFFF), [pmpaddr2] "r" (0xFFFFFFFF), [pmpaddr3] "r" (0xFFFFFFFF),
		[pmpaddr4] "r" (0xFFFFFFFF), [pmpaddr5] "r" (0xFFFFFFFF), [pmpaddr6] "r" (0xFFFFFFFF), [pmpaddr7] "r" (0xFFFFFFFF),
		[pmpaddr8] "r" (0xFFFFFFFF), [pmpaddr9] "r" (0xFFFFFFFF), [pmpaddra] "r" (0xFFFFFFFF), [pmpaddrb] "r" (0xFFFFFFFF),
		[pmpaddrc] "r" (0xFFFFFFFF), [pmpaddrd] "r" (0xFFFFFFFF), [pmpaddre] "r" (0xFFFFFFFF), [pmpaddrf] "r" (0xFFFFFFFF),
		[mepc] "r" (task_user_exeption), [bootaddr] "r" (0x1C008000), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data), [mpp_user] "r" (0) : "x15", "x14", "x18");

	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

	if(mcause != ILLEGAL_INSTR)
		error++;
	if (error != 0) printf("ERROR: X CAUSE failed\n");

	asm volatile (
			"csrrw x0, mtvec, %[bootaddr]\n"

			"la x14, return_here_illegal_2\n"
			"sw x14, 0(%[return_addr])\n"

			"mv x18, %[stack_data]\n"
			PUSH_ALL
			"csrrw x0, 0x041, %[uepc]\n"
			"uret\n"
			"return_here_illegal_2: \n"
			POP_ALL
			:  : [uepc] "r" (task_user_exeption), [bootaddr] "r" (0x1C008000), [return_addr] "r" (&return_here_instr), [stack_data] "r" (stack_data) : "x15", "x14", "x18");

	asm volatile (
			"csrrs %[mcause], 0x342, x0\n" : [mcause] "=r" (mcause));

	if(mcause != ILLEGAL_INSTR)
		error++;
	if (error != 0) printf("ERROR: X CAUSE failed\n");


	return error;

}

#endif

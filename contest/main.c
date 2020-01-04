#include <stdlib.h>
#include <stdio.h>
#define TEST_PATTERNS 16
#define TEST_CORE 0 

void __attribute__((noinline)) f1(void);
void __attribute__((noinline)) f2(void);
void __attribute__((noinline)) f3(void);
int __attribute__((noinline)) f4(int par);


int main ( void) {

int pattern[TEST_PATTERNS]= {
0x00000001,0x11111111,0x22222222,0x33333333,0x444444444,
0x55555555,0x66666666,0x77777777,0x88888888,0x999999999,
0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEEE,
0xFFFFFFFF
//		,0x0000000F,0x000000F0,0x00000F00,0x0000F000,0x000F0000,0x00F00000,0x0F00000,0xF0000000
//0x000000FF,0x00000FFF,0x0000FFFF,0x000FFFFF,0x00FFFFFF,0x0FFFFFFF,
//0x0F0f0f0f,0x00f00f00
};
volatile int a, b, c ;
volatile int res;
//COMPRESSED INSTRUCTIONS TODO
int i;
////////////////////////////////////////////////////
///////////// TESTING EXECUTION UNIT ///////////////
////////////////////////////////////////////////////
for ( i=0;i<TEST_PATTERNS;i++) {
a =pattern[i];
// addition
b =~pattern[i];
// + ->reading and writing  , = -> overwrite an existing register
asm volatile("add  %0,%1,%2": "+r" (c): "r" (a),"r" (b) );
res=c;
asm volatile("add  %0,%1,%2": "=r" (c): "r" (b),"r" (a) );
res=c;

//asm volatile (".option rvc\n\t c.add %0,%1,%2": "+r" (c):"r" (a), "r" (b));
res=c;
//asm volatile (".option norvc");
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
asm volatile ("p.abs %0,%1": "=r" (c): "r" (a) );
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
/*		asm volatile ("p.beqimm  %0,%1,%2\n\tno_jump_here:\n\tnop\n\tnop\n\tnop":: "r" (a),"i" (5), "i" (2) );
asm volatile ("p.bneimm %0,%1,%2\n\tjump_here:nop\n\tnop\n\tnop"::"r" (b) , "i" (4) , "i" (2));

*/
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
asm volatile ("pv.add.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.add.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.add.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.add.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.add.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.add.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.add.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.add.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.add.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.add.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00A));
res=c;

asm volatile ("pv.add.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.add.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00A));
res=c;

asm volatile ("pv.sub.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sub.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.sub.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sub.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.sub.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sub.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.sub.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sub.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.sub.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.sub.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;
asm volatile ("pv.sub.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.sub.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;


asm volatile ("pv.avg.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avg.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.avg.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avg.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.avg.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avg.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.avg.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avg.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.avg.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.avg.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;
asm volatile ("pv.avg.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.avg.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;


asm volatile ("pv.avgu.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avgu.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.avgu.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avgu.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.avgu.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avgu.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.avgu.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.avgu.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;
asm volatile ("pv.avgu.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.avgu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;
asm volatile ("pv.avgu.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.avgu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.min.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.min.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.min.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.min.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.min.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.min.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.min.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.min.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.min.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.min.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.min.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.min.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.minu.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.minu.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.minu.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.minu.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.minu.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.minu.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.minu.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.minu.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.minu.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.minu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.minu.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.minu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.max.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.max.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.max.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.max.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.max.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.max.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.max.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.max.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.max.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.max.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.max.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.max.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.maxu.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.maxu.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.maxu.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.maxu.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.maxu.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.maxu.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.maxu.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.maxu.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.maxu.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.maxu.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.maxu.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.maxu.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.srl.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.srl.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.srl.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.srl.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.srl.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.srl.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.srl.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.srl.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.srl.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.srl.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.srl.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.srl.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.sra.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sra.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sra.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sra.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sra.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sra.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sra.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sra.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sra.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.sra.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.sra.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.sra.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.sll.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sll.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sll.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sll.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sll.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sll.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sll.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.sll.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.sll.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.sll.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.sll.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.sll.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.or.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.or.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.or.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.or.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.or.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.or.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.or.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.or.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.or.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.or.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.or.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.or.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.xor.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.xor.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.xor.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.xor.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.xor.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.xor.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.xor.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.xor.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.xor.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.xor.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.xor.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.xor.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;



asm volatile ("pv.and.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.and.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.and.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.and.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.and.sc.b %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.and.sc.b %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.and.sc.h %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
res=c;
asm volatile ("pv.and.sc.h %0,%1,%2": "=r" (c): "r" (b) , "r" (a));
res=c;

asm volatile ("pv.and.sci.b %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.and.sci.b %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;

asm volatile ("pv.and.sci.h %0,%1,%2": "=r" (c): "r" (a) , "i" (0x005));
res=c;
asm volatile ("pv.and.sci.h %0,%1,%2": "=r" (c): "r" (b) , "i" (0x00a));
res=c;


asm volatile ("pv.insert.b %0,%1,%2": "=r" (c):"r" (a), "i" (2));
res=c;
asm volatile ("pv.insert.h %0,%1,%2": "=r" (c): "r" (a),"i" (1));
res=c;


asm volatile ("pv.extract.b %0,%1,%2": "=r" (c):  "r" (a), "i" (1));
res=c;
asm volatile ("pv.extract.h %0,%1,%2": "=r" (c):  "r" (a), "i" (1));
res=c;
asm volatile ("pv.extractu.b %0,%1,%2": "=r" (c):  "r" (a),"i" (1));
res=c;
asm volatile ("pv.extractu.h %0,%1,%2": "=r" (c): "r" (a), "i" (1));
res=c;





// dot products

asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;


asm volatile ("pv.dotup.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotup.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotup.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotup.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotup.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.dotup.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;



asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;
asm volatile ("pv.dotusp.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotusp.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotusp.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotusp.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.dotusp.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.dotusp.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;



asm volatile ("pv.dotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotsp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotsp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;
asm volatile ("pv.dotsp.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotsp.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.dotsp.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.dotsp.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotup.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotup.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;


asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;

asm volatile ("pv.sdotup.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotup.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.sdotup.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotup.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotup.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotup.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;



asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;
asm volatile ("pv.sdotusp.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotusp.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.sdotusp.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotusp.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotusp.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotusp.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;



asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;
asm volatile ("pv.sdotsp.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotsp.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.sdotsp.sc.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.sdotsp.sc.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

asm volatile ("pv.sdotsp.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.sdotsp.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;


// shuffle and pack instructions

asm volatile ("pv.shuffle.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.shuffle.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.shuffle.sci.h %0,%1,%2": "=r" (c) : "r" (a),"i" (5));
res=c;
asm volatile ("pv.shuffle.sci.h %0,%1,%2": "=r" (c) : "r" (b),"i" (10));
res=c;


asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.shuffleI0.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (3));
res=c;
asm volatile ("pv.shuffleI0.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
res=c;
asm volatile ("pv.shuffleI1.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (3));
res=c;
asm volatile ("pv.shuffleI1.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
res=c;
asm volatile ("pv.shuffleI2.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (3));
res=c;
asm volatile ("pv.shuffleI2.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
res=c;
asm volatile ("pv.shuffleI3.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (3));
res=c;
asm volatile ("pv.shuffleI3.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (3));
res=c;


asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.shuffle2.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.shuffle2.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;


asm volatile ("pv.pack.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.pack.h %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;
asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
res=c;
asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (b),"r" (a));
res=c;

// vectorial comparison operations
asm volatile("pv.cmpeq.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpeq.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpeq.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpeq.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpeq.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpeq.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpeq.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpeq.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpeq.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpeq.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpeq.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpeq.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;


asm volatile("pv.cmpne.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpne.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpne.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpne.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpne.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpne.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpne.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpne.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpne.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpne.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpne.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpne.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmpgt.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgt.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgt.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgt.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgt.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgt.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgt.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgt.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgt.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpgt.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpgt.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpgt.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmpge.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpge.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpge.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpge.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpge.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpge.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpge.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpge.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpge.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpge.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpge.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpge.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmplt.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmplt.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmplt.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmplt.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmplt.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmplt.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmplt.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmplt.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmplt.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmplt.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmplt.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmplt.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmple.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmple.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmple.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmple.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmple.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmple.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmple.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmple.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmple.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmple.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmple.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmple.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmpgtu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgtu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgtu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgtu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgtu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgtu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgtu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgtu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgtu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpgtu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpgtu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpgtu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmpgeu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgeu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgeu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgeu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgeu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgeu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgeu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpgeu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpgeu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpgeu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpgeu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpgeu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmpltu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpltu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpltu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpltu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpltu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpltu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpltu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpltu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpltu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpltu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpltu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpltu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

asm volatile("pv.cmpleu.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpleu.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpleu.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpleu.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpleu.sc.h %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpleu.sc.h %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpleu.sc.b %0,%1,%2": "=r" (c) : "r" (a) , "r" (b)  );
res=c;
asm volatile("pv.cmpleu.sc.b %0,%1,%2": "=r" (c) : "r" (b) , "r" (a)  );
res=c;
asm volatile("pv.cmpleu.sci.h %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpleu.sci.h %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;
asm volatile("pv.cmpleu.sci.b %0,%1,%2": "=r" (c) : "r" (a) , "i" (12)  );
res=c;
asm volatile("pv.cmpleu.sci.b %0,%1,%2": "=r" (c) : "r" (b) , "i" (12)  );
res=c;

// immediat instructions
asm volatile("addi %0 , %1, %2": "=r" (c) : "r" (a) , "i" (5));
res=c;
a=res;
asm volatile ("slti %0,%1,%2": "=r" (c): "r" (a), "i" (10));
res=c;
a=res;
asm volatile ("sltiu  %0,%1,%2": "=r" (c): "r" (a), "i" (5)); // 0x055
res=c;
a=res;
asm volatile("xori %0,%1,%2": "=r" (c): "r" (a), "i" (10));
res=c;
a=res;
asm volatile("ori %0,%1,%2": "=r" (c): "r" (a), "i" (5));
res=c;
a=res;
asm volatile ("andi %0,%1,%2": "=r" (c): "r" (a), "i" (10));
res=c;
a=res;
asm volatile("slli %0,%1,%2": "=r" (c): "r" (a), "i" (5));
res=c;
a=res;
asm volatile("srli %0,%1,%2": "=r" (c): "r" (a), "i" (10));
res=c;
a=res;
asm volatile("srai %0,%1,%2": "=r" (c): "r" (a), "i" (5));
res=c;
a=res;

}
// csr for pfp
asm volatile ("csrr %0, fcsr":"=r"(c));
res=c;
asm volatile ("csrw fcsr,%0"::"r"(c));
asm volatile ("csrr %0,fcsr":"=r" (c));
res=c;
// csr instructions
asm volatile ("rdcycle %0":"=r" (c));
res=c;
asm volatile ("rdtime %0": "=r" (c));
res=c;
asm volatile ("rdinstret %0": "=r" (c));
res =c;
/// hardware counters from 3 to 31 read and write all 1s

asm volatile ("csrr %0,hpmcounter3": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter3,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter3": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter4": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter4,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter4": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter5": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter5,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter5": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter6": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter6,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter6": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter7": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter7,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter7": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter8": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter8,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter8": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter9": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter9,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter9": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter10": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter10,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter10": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter11": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter11,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter11": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter12": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter12,%0":: "i" (0x0AAAAAAA));

asm volatile ("csrr %0,hpmcounter13": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter13,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter13": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter14": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter14,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter14": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter15": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter15,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter15": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter16": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter16,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter16": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter17": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter17,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter17": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter18": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter18,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter18": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter19": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter19,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter19": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter20": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter20,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter20": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter21": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter21,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter21": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter22": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter22,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter22": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter23": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter23,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter23": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter24": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter24,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter24": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter25": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter25,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter25": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter26": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter26,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter26": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter27": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter27,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter27": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter28": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter28,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter28": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter29": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter29,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter29": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter30": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter30,%0":: "i" (0x0AAAAAAA));
asm volatile ("csrr %0,hpmcounter30": "=r" (c));
res =c;

asm volatile ("csrr %0,hpmcounter31": "=r" (c));
res =c;
asm volatile ("csrw hpmcounter31,%0":: "i" (0x05555555));
asm volatile ("csrr %0,hpmcounter31": "=r" (c));
res =c;

// set and clear a specifi bit of a csr register
asm volatile ("csrs hpmcounter31,%0":: "r" (3));
asm volatile ("csrc hpmcounter31, %0":: "r" (3));


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

// csr fpr hardware loops
asm volatile ("csrr %0,0x7B0":"=r" (c));
res=c;
asm volatile ("csrw 0x7B0,%0":: "r" (c));
asm volatile ("csrr %0,0x7B0":"=r" (c));
res=c;

asm volatile ("csrr %0,0x7B1":"=r" (c));
res=c;
asm volatile ("csrw 0x7B1,%0":: "r" (c));
asm volatile ("csrr %0,0x7B1":"=r" (c));
res=c;

asm volatile ("csrr %0,0x7B2":"=r" (c));
res=c;
asm volatile ("csrw 0x7B2,%0":: "r" (c));
asm volatile ("csrr %0,0x7B2":"=r" (c));
res=c;

asm volatile ("csrr %0,0x7B3":"=r" (c));
res=c;
asm volatile ("csrw 0x7B3,%0":: "r" (c));
asm volatile ("csrr %0,0x7B3":"=r" (c));
res=c;

asm volatile ("csrr %0,0x7B4":"=r" (c));
res=c;
asm volatile ("csrw 0x7B4,%0":: "r" (c));
asm volatile ("csrr %0,0x7B4":"=r" (c));
res=c;

asm volatile ("csrr %0,0x7B5":"=r" (c));
res=c;
asm volatile ("csrw 0x7B5,%0":: "r" (c));
asm volatile ("csrr %0,0x7B5":"=r" (c));
res=c;


asm volatile ("csrr %0,0x7B6":"=r" (c));
res=c;
asm volatile ("csrw 0x7B6,%0":: "r" (c));
asm volatile ("csrr %0,0x7B6":"=r" (c));
res=c;

asm volatile ("csrr %0,0x7B7":"=r" (c));
res=c;
asm volatile ("csrw 0x7B7,%0":: "r" (c));
asm volatile ("csrr %0,0x7B7":"=r" (c));
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
asm volatile("csrw 0x780, %0":: "r" (c));asm volatile("csrr %0,0x780 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x781 ": "=r" (c));
res=c;
asm volatile("csrw 0x781, %0":: "r" (c));asm volatile("csrr %0,0x781 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x782 ": "=r" (c));
res=c;
asm volatile("csrw 0x782, %0":: "r" (c));asm volatile("csrr %0,0x782 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x783 ": "=r" (c));
res=c;
asm volatile("csrw 0x783, %0":: "r" (c));asm volatile("csrr %0,0x783 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x784 ": "=r" (c));
res=c;
asm volatile("csrw 0x784, %0":: "r" (c));asm volatile("csrr %0,0x784 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x785 ": "=r" (c));
res=c;
asm volatile("csrw 0x785, %0":: "r" (c));asm volatile("csrr %0,0x785 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x786 ": "=r" (c));
res=c;
asm volatile("csrw 0x786, %0":: "r" (c));asm volatile("csrr %0,0x786 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x787 ": "=r" (c));
res=c;
asm volatile("csrw 0x787, %0":: "r" (c));asm volatile("csrr %0,0x787 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x788 ": "=r" (c));
res=c;
asm volatile("csrw 0x788, %0":: "r" (c));asm volatile("csrr %0,0x788 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x789 ": "=r" (c));
res=c;
asm volatile("csrw 0x789, %0":: "r" (c));asm volatile("csrr %0,0x789 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x78a ": "=r" (c));
res=c;
asm volatile("csrw 0x78a, %0":: "r" (c));asm volatile("csrr %0,0x78a ": "=r" (c));
res=c;

asm volatile("csrr %0,0x78b ": "=r" (c));
res=c;
asm volatile("csrw 0x78b, %0":: "r" (c));asm volatile("csrr %0,0x78b ": "=r" (c));
res=c;

asm volatile("csrr %0,0x78c ": "=r" (c));
res=c;
asm volatile("csrw 0x78c, %0":: "r" (c));asm volatile("csrr %0,0x78c ": "=r" (c));
res=c;

asm volatile("csrr %0,0x78d ": "=r" (c));
res=c;
asm volatile("csrw 0x78d, %0":: "r" (c));asm volatile("csrr %0,0x78d ": "=r" (c));
res=c;

asm volatile("csrr %0,0x78e ": "=r" (c));
res=c;
asm volatile("csrw 0x78e, %0":: "r" (c));asm volatile("csrr %0,0x78e ": "=r" (c));
res=c;

asm volatile("csrr %0,0x78f ": "=r" (c));
res=c;
asm volatile("csrw 0x78f, %0":: "r" (c));asm volatile("csrr %0,0x78f ": "=r" (c));
res=c;

asm volatile("csrr %0,0x790 ": "=r" (c));
res=c;
asm volatile("csrw 0x790, %0":: "r" (c));asm volatile("csrr %0,0x790 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x791 ": "=r" (c));
res=c;
asm volatile("csrw 0x791, %0":: "r" (c));asm volatile("csrr %0,0x791 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x792 ": "=r" (c));
res=c;
asm volatile("csrw 0x792, %0":: "r" (c));asm volatile("csrr %0,0x792 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x793 ": "=r" (c));
res=c;
asm volatile("csrw 0x793, %0":: "r" (c));asm volatile("csrr %0,0x793 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x794 ": "=r" (c));
res=c;
asm volatile("csrw 0x794, %0":: "r" (c));asm volatile("csrr %0,0x794 ": "=r" (c));
res=c;

asm volatile("csrr %0,0x79f ": "=r" (c));
res=c;
asm volatile("csrw 0x79f, %0":: "r" (c));asm volatile("csrr %0,0x79f ": "=r" (c));
res=c;

// nope
asm volatile("nop");// converted into  addi x0,x0,0
//	int register	dummy_reg=asm ("x0");
//	res=dummy_reg;
///////////////////////////////////////////////////
//////////// TESTING REST OF CORE /////////////////
///////////////////////////////////////////////////
#if TEST_CORE

int dummy_vector[10000];
int dummy_vecort_2[10000];

// initialize data structure
for(i=0;i<10000;i++) {
dummy_vector[i]=i;
dummy_vector_2[i]=i;
}


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
// synchromize i/o and memory operations
asm volatile ("fence.I");
// atomic memory operations
asm volatile ("amoswap.w %0,%1,(%2) ": "=r" (c): "r" (a), "r" (pattern[3]) );
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

asm volatile ("li t0, 1 # Initialize swap value.\n\tagain:\n\t
amoswap.w.aq t0, t0, (a0) # Attempt to acquire lock.\n\t
bnez t0, again # Retry if held.\n\t
# Critical section.\n\t
addi %0,%0,1\n\t
amoswap.w.rl x0, x0, (a0) # Release lock by storing 0.": "=r" (c));
res=c;
// access to dummy vector increasing the stall due to cache miss
int index=0;
int dummy=0;
for (i=0;i<10000;i++){
index=dummy_vector_2[i];
dummy+=dummy_vector[index];
}
// access out of bound -> expr is generated by pmp
// pmp is not enable given from the fact that there is not possibility to access to the pmp's control registers
//	index=dummy_vector_2[i]; // how to handle exceptions??

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



volatile char act[8];
uint32_t word;

for(i = 0; i < 8; i++) act[i] = 0;
word = 0x01020304;
asm volatile ("sw %[a], 1(%[addr])\n"
: : [addr] "r" (act), [a] "r" (word));

for(i = 0; i < 8; i++) act[i] = 0;
word = 0x01020304;
asm volatile ("sw %[a], 2(%[addr])\n"
: : [addr] "r" (act), [a] "r" (word));

for(i = 0; i < 8; i++) act[i] = 0;
word = 0x01020304;
asm volatile ("sw %[a], 3(%[addr])\n"
: : [addr] "r" (act), [a] "r" (word));

for(i = 0; i < 8; i++) act[i] = 0;
word = 0x0304;
asm volatile ("sh %[a], 1(%[addr])\n"
: : [addr] "r" (act), [a] "r" (word));



for(i = 0; i < 8; i++) act[i] = 0;
word = 0x0304;
asm volatile ("sh %[a], 2(%[addr])\n"
: : [addr] "r" (act), [a] "r" (word));



for(i = 0; i < 8; i++) act[i] = 0;
word = 0x0304;
asm volatile ("sh %[a], 3(%[addr])\n"
: : [addr] "r" (act), [a] "r" (word));

//load and store conditional ops ( from risc v spec )
asm volatile ("# a0 holds address of memory location\n\t
# a1 holds expected value\n\t
# a2 holds desired value\n\t
# a0 holds return value, 0 if successful, !0 otherwise\n\t
cas:\n\t
lr.w t0, %0 # Load original value.\n\t
bne t0, a1, fail # Doesn’t match, so fail.\n\t
sc.w t0, a2, %0 # Try to update.\n\t
bnez t0, cas # Retry if store-conditional failed.
fail:
": : "r" (c));
res=c;
// load and store instructions (pulp extension)
//Register-Immediate Loads with Post-Increment
b=0;
asm volatile ("p.lb %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
asm volatile ("p.sb %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
b=0;
asm volatile ("p.lbu %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
asm volatile ("p.sb %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
b=0;
asm volatile ("p.lh %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
asm volatile ("p.sh %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
b=0;
asm volatile ("p.lhu %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
asm volatile ("p.sh %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
b=0;
asm volatile ("p.lw %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
asm volatile ("addi %0,%1, 1":"=r" (c): "r" (c));
asm volatile ("p.sw %0,%1(%2!)": "=r" (c): "i" (dummy_vector), "r" (b));
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

// normal  loops
int dummy_2=0;
for(int k=0;k<3;k++) {
for(int j=0;j<3;j++) {
dummy++;
dummy_2++;
}
}
//-----------------------------------------------------------------
// Check HWLOOP with lp.starti/lp.endi/lp.count
//-----------------------------------------------------------------
// RVC -> compressed instructions
// no RVC
i = 0;
int  j = 0;
int tmp=3;
asm volatile (
".option norvc;"
"lp.count x0, %[N];"
"lp.endi x0, end44;"
"lp.starti x0, start44;"
"start44: addi %[i], %[i], 1;"
"end44: addi %[j], %[j], 10;"
: [i] "+r" (i), [j] "+r" (j)
: [N] "r" (10)
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
"mv %[tmp2], a1;"
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
"mv a1, %[tmp2];"
: [i] "+r" (i), [j] "+r" (j), [tmp] "+r" (tmp), [tmp2] "+r" (tmp2)
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
//register file TODO
// ecall and ret + saving regs on stack
f1();
#endif
return EXIT_SUCCESS;
}



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

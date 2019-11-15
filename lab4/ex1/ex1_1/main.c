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

int main(int argc, char *argv[])
{
	int pattern [6] = {0x00000000, 0x0000FFFF, 0x00FF00FF, 0x0F0F0F0F, 0x33333333, 0x55555555};	
	int i;
	volatile int a;
	volatile int c;	
	// hint to the compiler for putting the variable into a register (ATTENTION it will not force it ) 
	/*testing integer register file with differetnt pattern for each register */
	for ( i=0;i<6;i++) {
		register int x1 asm("x1");

		a= pattern[i];	  
		x1=a;
		c=x1;	

		a= !pattern[i];
		x1=a;
		c=x1; 

		register int x2 asm("x2");

		a= pattern[i];	  
		x2=a;
		c=x2;	

		a= !pattern[i];
		x2=a;
		c=x2; 
		register int x3 asm("x3");

		a= pattern[i];	  
		x3=a;
		c=x3;	

		a= !pattern[i];
		x3=a;
		c=x3; 
		register int x4 asm("x4");

		a= pattern[i];	  
		x4=a;
		c=x4;	

		a= !pattern[i];
		x4=a;
		c=x4; 
		register int x5 asm("x5");

		a= pattern[i];	  
		x5=a;
		c=x5;	

		a= !pattern[i];
		x5=a;
		c=x5; 
		register int x6 asm("x6");

		a= pattern[i];	  
		x6=a;
		c=x6;	

		a= !pattern[i];
		x6=a;
		c=x6; 
		register int x7 asm("x7");

		a= pattern[i];	  
		x7=a;
		c=x7;	

		a= !pattern[i];
		x7=a;
		c=x7; 
		register int x8 asm("x8");

		a= pattern[i];	  
		x8=a;
		c=x8;	

		a= !pattern[i];
		x8=a;
		c=x8; 
		register int x9 asm("x9");

		a= pattern[i];	  
		x9=a;
		c=x9;	

		a= !pattern[i];
		x9=a;
		c=x9; 
		register int x10 asm("x10");

		a= pattern[i];	  
		x10=a;
		c=x10;	

		a= !pattern[i];
		x10=a;
		c=x10; 
		register int x11 asm("x11");

		a= pattern[i];	  
		x11=a;
		c=x11;	

		a= !pattern[i];
		x11=a;
		c=x11; 
		register int x12 asm("x12");

		a= pattern[i];	  
		x12=a;
		c=x12;	

		a= !pattern[i];
		x12=a;
		c=x12; 
		register int x13 asm("x13");

		a= pattern[i];	  
		x13=a;
		c=x13;	

		a= !pattern[i];
		x13=a;
		c=x13; 
		register int x14 asm("x14");

		a= pattern[i];	  
		x14=a;
		c=x14;	

		a= !pattern[i];
		x14=a;
		c=x14; 
		register int x15 asm("x15");

		a= pattern[i];	  
		x15=a;
		c=x15;	

		a= !pattern[i];
		x15=a;
		c=x15; 
		register int x16 asm("x16");

		a= pattern[i];	  
		x16=a;
		c=x16;	

		a= !pattern[i];
		x16=a;
		c=x16; 
		register int x17 asm("x17");

		a= pattern[i];	  
		x17=a;
		c=x17;	

		a= !pattern[i];
		x17=a;
		c=x17; 
		register int x18 asm("x18");

		a= pattern[i];	  
		x18=a;
		c=x18;	

		a= !pattern[i];
		x18=a;
		c=x18; 
		register int x19 asm("x19");

		a= pattern[i];	  
		x19=a;
		c=x19;	

		a= !pattern[i];
		x19=a;
		c=x19; 
		register int x20 asm("x20");

		a= pattern[i];	  
		x20=a;
		c=x20;	

		a= !pattern[i];
		x20=a;
		c=x20; 
		register int x21 asm("x21");

		a= pattern[i];	  
		x21=a;
		c=x21;	

		a= !pattern[i];
		x21=a;
		c=x21; 
		register int x22 asm("x22");

		a= pattern[i];	  
		x22=a;
		c=x22;	

		a= !pattern[i];
		x22=a;
		c=x22; 
		register int x23 asm("x23");

		a= pattern[i];	  
		x23=a;
		c=x23;	

		a= !pattern[i];
		x23=a;
		c=x23; 
		register int x24 asm("x24");

		a= pattern[i];	  
		x24=a;
		c=x24;	

		a= !pattern[i];
		x24=a;
		c=x24; 
		register int x25 asm("x25");

		a= pattern[i];	  
		x25=a;
		c=x25;	

		a= !pattern[i];
		x25=a;
		c=x25; 
		register int x26 asm("x26");

		a= pattern[i];	  
		x26=a;
		c=x26;	

		a= !pattern[i];
		x26=a;
		c=x26; 
		register int x27 asm("x27");

		a= pattern[i];	  
		x27=a;
		c=x27;	

		a= !pattern[i];
		x27=a;
		c=x27; 
		register int x28 asm("x28");

		a= pattern[i];	  
		x28=a;
		c=x28;	

		a= !pattern[i];
		x28=a;
		c=x28; 
		register int x29 asm("x29");

		a= pattern[i];	  
		x29=a;
		c=x29;	

		a= !pattern[i];
		x29=a;
		c=x29; 
		register int x30 asm("x30");

		a= pattern[i];	  
		x30=a;
		c=x30;	

		a= !pattern[i];
		x30=a;
		c=x30; 
		register int x31 asm("x31");

		a= pattern[i];	  
		x31=a;
		c=x31;	

		a= !pattern[i];
		x31=a;
		c=x31; 
		register int x32 asm("x32");

		a= pattern[i];	  
		x32=a;
		c=x32;	

		a= !pattern[i];
		x32=a;
		c=x32; 
		register  int x0 asm("x0");

		a= pattern[i];	  
		x0=a;
		c=x0;	

		a= !pattern[i];
		x0=a;
		c=x0; 	
	}
	/*testing floating point register file */
	for( i=0;i<6;i++) {
		register int x1 asm("f1");

		a= pattern[i];	  
		x1=a;
		c=x1;	

		a= !pattern[i];
		x1=a;
		c=x1; 

		register int x2 asm("f2");

		a= pattern[i];	  
		x2=a;
		c=x2;	

		a= !pattern[i];
		x2=a;
		c=x2; 
		register int x3 asm("f3");

		a= pattern[i];	  
		x3=a;
		c=x3;	

		a= !pattern[i];
		x3=a;
		c=x3; 
		register int x4 asm("f4");

		a= pattern[i];	  
		x4=a;
		c=x4;	

		a= !pattern[i];
		x4=a;
		c=x4; 
		register int x5 asm("f5");

		a= pattern[i];	  
		x5=a;
		c=x5;	

		a= !pattern[i];
		x5=a;
		c=x5; 
		register int x6 asm("f6");

		a= pattern[i];	  
		x6=a;
		c=x6;	

		a= !pattern[i];
		x6=a;
		c=x6; 
		register int x7 asm("f7");

		a= pattern[i];	  
		x7=a;
		c=x7;	

		a= !pattern[i];
		x7=a;
		c=x7; 
		register int x8 asm("f8");

		a= pattern[i];	  
		x8=a;
		c=x8;	

		a= !pattern[i];
		x8=a;
		c=x8; 
		register int x9 asm("f9");

		a= pattern[i];	  
		x9=a;
		c=x9;	

		a= !pattern[i];
		x9=a;
		c=x9; 
		register int x10 asm("f10");

		a= pattern[i];	  
		x10=a;
		c=x10;	

		a= !pattern[i];
		x10=a;
		c=x10; 
		register int x11 asm("f11");

		a= pattern[i];	  
		x11=a;
		c=x11;	

		a= !pattern[i];
		x11=a;
		c=x11; 
		register int x12 asm("f12");

		a= pattern[i];	  
		x12=a;
		c=x12;	

		a= !pattern[i];
		x12=a;
		c=x12; 
		register int x13 asm("f13");

		a= pattern[i];	  
		x13=a;
		c=x13;	

		a= !pattern[i];
		x13=a;
		c=x13; 
		register int x14 asm("f14");

		a= pattern[i];	  
		x14=a;
		c=x14;	

		a= !pattern[i];
		x14=a;
		c=x14; 
		register int x15 asm("f15");

		a= pattern[i];	  
		x15=a;
		c=x15;	

		a= !pattern[i];
		x15=a;
		c=x15; 
		register int x16 asm("f16");

		a= pattern[i];	  
		x16=a;
		c=x16;	

		a= !pattern[i];
		x16=a;
		c=x16; 
		register int x17 asm("f17");

		a= pattern[i];	  
		x17=a;
		c=x17;	

		a= !pattern[i];
		x17=a;
		c=x17; 
		register int x18 asm("f18");

		a= pattern[i];	  
		x18=a;
		c=x18;	

		a= !pattern[i];
		x18=a;
		c=x18; 
		register int x19 asm("f19");

		a= pattern[i];	  
		x19=a;
		c=x19;	

		a= !pattern[i];
		x19=a;
		c=x19; 
		register int x20 asm("f20");

		a= pattern[i];	  
		x20=a;
		c=x20;	

		a= !pattern[i];
		x20=a;
		c=x20; 
		register int x21 asm("f21");

		a= pattern[i];	  
		x21=a;
		c=x21;	

		a= !pattern[i];
		x21=a;
		c=x21; 
		register int x22 asm("f22");

		a= pattern[i];	  
		x22=a;
		c=x22;	

		a= !pattern[i];
		x22=a;
		c=x22; 
		register int x23 asm("f23");

		a= pattern[i];	  
		x23=a;
		c=x23;	

		a= !pattern[i];
		x23=a;
		c=x23; 
		register int x24 asm("f24");

		a= pattern[i];	  
		x24=a;
		c=x24;	

		a= !pattern[i];
		x24=a;
		c=x24; 
		register int x25 asm("f25");

		a= pattern[i];	  
		x25=a;
		c=x25;	

		a= !pattern[i];
		x25=a;
		c=x25; 
		register int x26 asm("f26");

		a= pattern[i];	  
		x26=a;
		c=x26;	

		a= !pattern[i];
		x26=a;
		c=x26; 
		register int x27 asm("f27");

		a= pattern[i];	  
		x27=a;
		c=x27;	

		a= !pattern[i];
		x27=a;
		c=x27; 
		register int x28 asm("f28");

		a= pattern[i];	  
		x28=a;
		c=x28;	

		a= !pattern[i];
		x28=a;
		c=x28; 
		register int x29 asm("f29");

		a= pattern[i];	  
		x29=a;
		c=x29;	

		a= !pattern[i];
		x29=a;
		c=x29; 
		register int x30 asm("f30");

		a= pattern[i];	  
		x30=a;
		c=x30;	

		a= !pattern[i];
		x30=a;
		c=x30; 
		register int x31 asm("f31");

		a= pattern[i];	  
		x31=a;
		c=x31;	

		a= !pattern[i];
		x31=a;
		c=x31; 
		register int x32 asm("f32");

		a= pattern[i];	  
		x32=a;
		c=x32;	

		a= !pattern[i];
		x32=a;
		c=x32; 
		register  int x0 asm("f0");

		a= pattern[i];	  
		x0=a;
		c=x0;	

		a= !pattern[i];
		x0=a;
		c=x0; 


	}

	return EXIT_SUCCESS;
}

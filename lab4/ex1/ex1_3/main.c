#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int test_values[16]= {0x00000000,0x11111111,0x22222222,0x33333333,0x444444444,0x55555555,0x66666666,
		0x77777777,0x8888888,0x99999999,0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEE,0xFFFFFFFF};
	int i,j;
	volatile int res;
	register int a ;
	register int b;
	register int c ;

	for(j=0;j<16; j++) {
		b=test_values[j];

		for(i=j;i<16;i++) {
			a=test_values[i];
			asm volatile("mul %0,%1,%2": "=r" (c) :"r" (a), "r" (b));
			res=c;

			asm volatile ("mulh %0,%1,%2": "=r" (c) :"r" (a), "r" (b));
			res=c;
			asm volatile ("mulhu %0,%1,%2": "=r" (c) :"r" (a), "r" (b));
			res=c;
			asm volatile  ("mulhsu %0,%1,%2": "=r" (c) :"r" (a), "r" (b));
			res=c;

			/// extensions

			asm volatile ("p.mac %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.msu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.muls %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulhhs %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulhhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulhhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulhhu %0,%1,%2": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.muluN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulhhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.muluRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.mulhhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.macsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.machhsN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.macsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.machhsRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.macuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.machhuN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.macuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("p.machhuRN %0,%1,%2,3": "=r" (c): "r" (a) , "r" (b));
			res=c;
			asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;

			asm volatile ("pv.dotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.dotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
			res=c;
			asm volatile ("pv.dotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
			res=c;
			asm volatile ("pv.dotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.dotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
			res=c;
			asm volatile ("pv.dotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
			res=c;

			asm volatile ("pv.dotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.dotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
			res=c;
			asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
			res=c;

			asm volatile ("pv.sdotup.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.sdotup.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
			res=c;
			asm volatile ("pv.sdotup.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
			res=c;

			asm volatile ("pv.sdotusp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.sdotusp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
			res=c;
			asm volatile ("pv.sdotusp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
			res=c;


			asm volatile ("pv.sdotsp.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.sdotsp.sc.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (a),"i" (0x00f));
			res=c;
			asm volatile ("pv.sdotsp.sci.b %0,%1,%2": "=r" (c) : "r" (b),"i" (0x00f));
			res=c;

			asm volatile ("pv.shuffle.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;

			asm volatile ("pv.shuffle2.h %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.shuffle2.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.packhi.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("pv.packlo.b %0,%1,%2": "=r" (c) : "r" (a),"r" (b));
			res=c;
			asm volatile ("p.addRN %0,%1,%2,5": "=r" (c) : "r" (a),"r" (b));
			res=c;
		}
	}

	return EXIT_SUCCESS;
}

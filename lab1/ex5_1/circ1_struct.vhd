LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ1 IS
PORT (a,b,c:IN std_logic;
	w,z:OUT std_logic);
END ENTITY circ1;

ARCHITECTURE struc OF circ1 IS

	SIGNAL z1,b1,f,c1,c2,c3,e1,e2,d,l,h,e: std_logic;


BEGIN

d<=not(a);

z<=d and z1;

z1<= h or  l ;

l<= f and b1;

f<= not ( c1);


w<= c2 and e1; 

h<= e2 and c3;

e<=not(b);

e2<=e;
e1<=e;
c1<=c;
c2<=c;
c3<=c;

END struc;

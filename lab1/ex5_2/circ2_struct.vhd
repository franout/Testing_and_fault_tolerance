LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ2 IS
PORT (a,b,c:IN std_logic;
	y,z:OUT std_logic);
END ENTITY circ2;

ARCHITECTURE struc OF circ2 IS

	SIGNAL z1,b1,f,c1,c2,c3,e1,e2,d,l,h,e: std_logic;

BEGIN
d<= a and b1;
g<= d or e;
y<=g;
h<=g;

b1<=b;
b2<=b;
b3<=b;
e<= not( b2 and c1);
c1<=c;
c2<=c;

b31<=b3;
b32<=b3;

f<= c2 xor b31;

k<=h and f;

z<= k xor b32;




END struc;

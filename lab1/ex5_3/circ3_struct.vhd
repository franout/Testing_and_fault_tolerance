LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ3 IS
PORT (a,b,c,d,e:IN std_logic;
	y,z:OUT std_logic);
END ENTITY circ3;

ARCHITECTURE struc OF circ3 IS


BEGIN


n4<= not( e and n11);
y<= not ( n4 and n31);
z<= not ( n32 and n2);

n2<= not ( a and c2);

n31<=n3;
n32<=n3;

n3<= not ( n12 and b );

n11<=n1;
n12<=n1;
 n1<=not ( d and c1);

c1<= c;
c2<=c;









END struc;

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ1 IS
PORT (a,b,c:IN std_logic;
	w,z:OUT std_logic);
END ENTITY circ1;

ARCHITECTURE beh OF circ1 IS

BEGIN

z<=(not(a))and ( (not(b)and c)or ((not(c)and b)));
w<=(not(b)) and c;




END struc;
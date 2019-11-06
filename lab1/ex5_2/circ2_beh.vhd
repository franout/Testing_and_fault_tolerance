LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ2 IS
PORT (a,b,c:IN std_logic;
	y,z:OUT std_logic);
END ENTITY circ2;

ARCHITECTURE beh OF circ2 IS
SIGNAL y_i: std_logic;
BEGIN

y<=y_i;
y_i<=(a and b ) or (not (b and c));

z <= (y_i and (c xor b)) xor b;


END beh;

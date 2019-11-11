LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ3 IS
PORT (a,b,c,e,f:IN std_logic;
	y,z:OUT std_logic);
END ENTITY circ3;

ARCHITECTURE beh OF circ3 IS
SIGNAL y_i: std_logic;
BEGIN

y<=not(not(not(a and c) and f) and not(not(c and a) and b));

z<= not ( (not(a and c) and (not( b and ( not  ( a and c ) ) )) ));


END beh;

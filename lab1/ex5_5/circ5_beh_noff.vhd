LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ5 IS
PORT ( clk, reset, a,b,c,d: IN std_logic;
		y: OUT std_logic);
END ENTITY circ5;

ARCHITECTURE beh OF circ5 IS

SIGNAL ffs: std_logic_vector(2 DOWNTO 0 );
SIGNAL q1,q2,q0,y_i,q11,q22: std_logic;

BEGIN

q2<= y_i;
q1<= not ( b  or q11);
q0<= not ( y_i or not( d) );


y<= not (y_i) ;
y_i<= not ( ffs(0) or (not ( ( q11 or q22 )  and ( c or q22 )   )) );

q11<= not ( ffs(1) or a);

q22<= ffs(2) and (not d);



END beh;

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ6 IS
PORT ( clk, reset, x: IN std_logic;
		y: OUT std_logic);
END ENTITY circ6;

ARCHITECTURE beh OF circ6 IS

SIGNAL ffs: std_logic_vector(1 DOWNTO 0 );
SIGNAL q1,q2,q0,y_i,q11,q22: std_logic;


BEGIN

y<= ffs(1) and x and (not ( ffs(0)));


q1<= (ffs(1) and ffs(0)) or  (x and ffs(0)) ;
q0<= x;


END beh;

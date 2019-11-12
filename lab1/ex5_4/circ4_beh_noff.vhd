LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ4 IS
PORT ( clk, reset, cnt: IN std_logic;
		y: OUT std_logic);
END ENTITY circ4;


ARCHITECTURE beh OF circ4 IS 
SIGNAL ffs: std_logic_vector( 1 DOWNTO 0);
SIGNAL d1,d2: std_logic;


BEGIN 



y<= ffs(0) and ffs(1);

d1<= cnt xor ffs(1);

d2<=(not(cnt) and ffs(0))xor (not(ffs(1)) and ffs(0) and cnt ) xor( not (ffs(0) and ffs(1) and cnt));


END beh;

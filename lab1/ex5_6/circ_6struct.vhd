LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ6 IS
PORT ( clk, reset, x: IN std_logic;
		y: OUT std_logic);
END ENTITY circ6;

ARCHITECTURE struc OF circ6 IS


COMPONENT ff IS
PORT (clk,reset,d: IN std_logic;
q,qn: OUT std_logic);
END COMPONENT ff;

SIGNAL x1,x2,x3,a,b,c,d12,d11,d01,d02,d1,reset1,reset2,clk1,clk2: std_logic;

 BEGIN 

f0:ff PORT MAP (clk=> clk1,reset=> reset1,d=> c,q=> d0,qn=>'0');
f1: ff PORT MAP (clk=> clk2 , reset => reset2 ,d=> x3,q=>d1,qn=>'0');


x1<= x;
x2<= x;
x3<= x;



a <= d12 and d01;
b <= d11 and x1M
c<= a or b ;

d12<= d1;
d11<= d1;

d01<= d0;
d02<= d0;

y<= d02 and x2 and d2n;



reset1<= reset;
reset2<= reset;
clk1<= clk;
clk2 <= clk;





END struc;

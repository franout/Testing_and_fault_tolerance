LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ4 IS
PORT ( clk, reset, cnt: IN std_logic;
		y: OUT std_logic);
END ENTITY circ4;

ARCHITECTURE struc OF circ4 IS


COMPONENT ff IS
PORT (clk,reset,d: IN std_logic;
q,qn: OUT std_logic);
END COMPONENT ff;

SIGNAL q1,qn1,a,q2,qn2,b,q11,q12,q13,q21,q22,q23,q24,b,c,d,f,cnt1,cnt2,cnt3,cnt4,cnt5,cnt6: std_logic;

BEGIN

ff1: ff PORT MAP(clk=>clk,reset=>reset,q=> q1 ,qn=>qn1,d=>a);
ff2: ff PORT MAP(clk=>clk,reset=>reset,q=> q2,qn=> qn2, d=> b);



q11<=q1;
q12<=q11;
q13<=q11;


a<=q12 xor cnt1;
y<= q12 and q21;

q21<=q2;
q22<=q2;
q23<=q22;
q24<=q22;


b<= c xor d xor f;

c<= q23 and qn1 and cnt3;
d<= q24 and cnt5;
 f<=qn2 and cnt6 and cnt6;

cnt1<=cnt;
cnt2<=cnt;
cnt3<=cnt2;
cnt4<=cnt2;
cnt5<=not(cnt4);
cnt6<=cnt2;

END struc;

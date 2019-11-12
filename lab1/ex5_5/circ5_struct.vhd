LIBRARY ieee;
USE ieee.std_logic_1164.ALL;


ENTITY  circ5 IS
PORT ( clk, reset, a,b,c,d: IN std_logic;
		y: OUT std_logic);
END ENTITY circ5;

ARCHITECTURE struc OF circ5 IS


COMPONENT ff IS
PORT (clk,reset,d: IN std_logic;
q,qn: OUT std_logic);
END COMPONENT ff;

SIGNAL yi_1,yi_2,yi_3,d0,d1,d2,yi_21,yi_22,f,e,d1,d2,d3,m ,m1,m2,k,h,g,aa,aa1,aa2 : std_logic;

BEGIN


f0: ff PORT MAP(clk=>clk,reset=>reset, d=>f,q=>d0,qn=>'0');
f1: ff PORT MAP(clk=>clk,reset=>reset,d=>e,q=>d1,qn=>'0');
f2: ff PORT MAP (clk=>clk,reset=>reset, d=> yi_22,q=>d2,qn=>'0');



y<= not ( y_i3);

yi_3<=yi_1;
yi_2<= yi_1;
yi_1<= not ( d0 or g);


yi_21<= yi_2;
yi_22<= yi_2;

f<=not ( d2 or yi_21 );

m<= d2 and d3;
m1<=m;
m2<= m;
l<= m1 or c;
h<= m2 or aa1;

g<= not ( h and l );

e<=not ( b or aa2);


aa1<=aa;
aa2<=aa;
aa<= not ( a or d1 );

d1<= not (d);
d2<= d1;
d3<= d1;

END struc;

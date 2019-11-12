LIBRARY ieee;
USE ieee.std_logic_1164.ALL;



ENTITY ff IS
PORT (clk,reset,d: IN std_logic;
q,qn: OUT std_logic);
END ENTITY ff;


ARCHITECTURE beh OF ff IS



regs:PROCESS(clk,reset)
BEGIN 
IF (reset='1') THEN
q<='0';
qn<='1';
ELSE
	IF(clk='1' and clk'EVENT) THEN 
	q<=d;
	qn<=not(d);
	END IF;

END IF ;
END PROCESS regs;


END beh;
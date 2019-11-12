
library std;
use std.env.all;
use std.textio.all;


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_textio.all;

entity tb_ex5_5 is
end tb_ex5_5;


architecture tb of tb_ex5_5 is
COMPONENT  circ5 IS
PORT ( clk, reset, a,b,c,d: IN std_logic;
		y: OUT std_logic);
END COMPONENT circ5;

	constant clock_t1      : time := 50 ns;
	constant clock_t2      : time := 30 ns;
	constant clock_t3      : time := 20 ns;
	constant apply_offset  : time := 0 ns;
	constant apply_period  : time := 100 ns;
	constant strobe_offset : time := 40 ns;
	constant strobe_period : time := 100 ns;


	signal tester_clock : std_logic := '0';

    signal A : std_logic;
    signal B,C,D,reset : std_logic;
    signal Y: std_logic;

begin

    cut : circ5
    port map (clk=>tester_clock,reset=> reset , a=> A, b=>B,c=> C,d=> D,y=>Y);

-- ***** CLOCK ***********************************

	clock_generation : process
	begin
		loop
			wait for clock_t1; tester_clock <= '1';
			wait for clock_t2; tester_clock <= '0';
			wait for clock_t3;
		end loop;
	end process;

-- ***** STIMULI *********************************

    stimuli : process
		procedure apply_pattern (
			constant A_val : in std_logic;
			constant B_val : in std_logic;
			constant C_val : in std_logic;
			constant D_val : in std_logic;
			constant Res_val : in std_logic;

			signal A : out std_logic;
			signal B : out std_logic;
			signal C : out std_logic;
			signal D : out std_logic;
			signal reset : out std_logic ) is
		begin
			A <= A_val;
			B <= B_val;
			C<= C_val;
			D <= D_val;
			reset <= Res_val;
			wait for apply_period;
		end apply_pattern;
    begin
        
		wait for apply_offset;

		apply_pattern('0', '0','0','0','0', A, B,C,D,reset);
			apply_pattern('0', '0','0','0','1', A, B,C,D,reset);
		apply_pattern('0', '1','1','0','1', A, B,C,D,reset);

		apply_pattern('0', '0','0','1','0', A, B,C,D,reset);
		apply_pattern('0', '0','1','0','0', A, B,C,D,reset);
		apply_pattern('0', '0','1','1','0', A, B,C,D,reset);
		apply_pattern('0', '1','0','0','0', A, B,C,D,reset);
		apply_pattern('0', '1','0','1','0', A, B,C,D,reset);
		apply_pattern('0', '1','1','0','0', A, B,C,D,reset);
		apply_pattern('1', '0','0','1','0', A, B,C,D,reset);
		apply_pattern('1', '0','1','0','0', A, B,C,D,reset);
		apply_pattern('1', '0','1','1','0', A, B,C,D,reset);

		apply_pattern('1', '1','0','0','0', A, B,C,D,reset);
		apply_pattern('1', '1','0','1','0', A, B,C,D,reset);
		apply_pattern('1', '1','1','0','0', A, B,C,D,reset);
		apply_pattern('1', '1','1','1','0', A, B,C,D,reset);

	

		-- Stop the simulation
		finish(0);
    end process;

-- ****** MONITOR ************************************
	
	monitor : process
		variable counter  : integer := 0;
		variable pis      : std_logic_vector(3 downto 0);
		variable pos      : std_logic_vector(1 downto 0);
		file     outfile  : text open WRITE_MODE is "monitor.txt";
		variable outline  : line;

		function vec2str( input : std_logic_vector ) return string is
			variable rline : line;
		begin
			write( rline, input );
			return rline.all;
		end vec2str;

	begin
		wait for strobe_offset;

		loop
			pis := A & B &C &D;
			pos := Y &"Z" ;
			write(outline, "pattern:" & integer'image(counter) & " PIs:" &  vec2str(pis) & " POs:" &  vec2str(pos));
			tee(outfile, outline);
			counter := counter + 1;
			wait for strobe_period;
		end loop;

	end process;

-- ****************************************************

end tb;



configuration cfg_tb_ex5_5 of tb_ex5_5 is
    for tb
    end for;
end cfg_tb_ex5_5;

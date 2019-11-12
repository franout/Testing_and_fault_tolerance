
library std;
use std.env.all;
use std.textio.all;


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_textio.all;

entity tb_ex5_6 is
end tb_ex5_6;


architecture tb of tb_ex5_6 is
COMPONENT  circ6 IS
PORT ( clk, reset, x: IN std_logic;
		y: OUT std_logic);
END COMPONENT circ6;
	constant clock_t1      : time := 50 ns;
	constant clock_t2      : time := 30 ns;
	constant clock_t3      : time := 20 ns;
	constant apply_offset  : time := 0 ns;
	constant apply_period  : time := 100 ns;
	constant strobe_offset : time := 40 ns;
	constant strobe_period : time := 100 ns;


	signal tester_clock : std_logic := '0';

    signal X : std_logic;
    signal reset : std_logic;
    signal Y: std_logic;

begin

    cut : circ6
    port map (clk=>tester_clock,reset=>reset,x=>X);

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
			constant X_val : in std_logic;
			constant reset_val : in std_logic;
			signal x : out std_logic;
			signal reset : out std_logic ) is
		begin
			X<= x_val;
			reset <= reset_val;
			wait for apply_period;
		end apply_pattern;
    begin
        
		wait for apply_offset;

		apply_pattern('0', '0', x, reset);
		apply_pattern('0', '1', x, reset);

		apply_pattern('1', '1', x, reset);
		apply_pattern('0', '0', x, reset);
		apply_pattern('1', '0', x, reset);
		apply_pattern('1', '0', x, reset);
		apply_pattern('1', '0', x, reset);
		apply_pattern('1', '0', x, reset);
		apply_pattern('1', '0', x, reset);


		-- Stop the simulation
		finish(0);
    end process;

-- ****** MONITOR ************************************
	
	monitor : process
		variable counter  : integer := 0;
		variable pis      : std_logic_vector(4 downto 0);
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
			pis := X & reset ;
			pos := Y ;
			write(outline, "pattern:" & integer'image(counter) & " PIs:" &  vec2str(pis) & " POs:" &  vec2str(pos));
			tee(outfile, outline);
			counter := counter + 1;
			wait for strobe_period;
		end loop;

	end process;

-- ****************************************************

end tb;



configuration cfg_tb_ex5_6 of tb_ex5_6 is
    for tb
    end for;
end cfg_tb_ex5_6;

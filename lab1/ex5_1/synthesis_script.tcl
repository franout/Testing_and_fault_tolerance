set search_path {..}

uplevel #0 source ../../library/pdt2002.dc_setup.tcl

analyze -library work -format vhdl ex5_1_beh.vhd
elaborate ex5_1
#create_clock -name "clk" -period 200 -waveform { 100 200 } { clk }
#create_clock -name "rst" -period 200 -waveform { 100 200 } { rst }

#compile -exact_map
compile_ultra

report_design
report_area -nosplit
#report_clock -nosplit

write -hierarchy -format verilog -output ../ex5_1_synth.v
write -hierarchy -format vhdl -output ../ex5_1_synth.vhd

quit

set search_path {..}

uplevel #0 source $env(LIB_PATH)/pdt2002.dc_setup.tcl

analyze -library work -format vhdl $env(CIRCUIT)_$env(ARC).vhd
elaborate $env(EXE_N)
#create_clock -name "clk" -period 200 -waveform { 100 200 } { clk }
#create_clock -name "rst" -period 200 -waveform { 100 200 } { rst }

#compile -exact_map
compile_ultra

report_design
report_area -nosplit
#report_clock -nosplit

write -hierarchy -format verilog -output ../$env(EXE_N)_synth.v
write -hierarchy -format vhdl -output ../$env(EXE_N)_synth.vhd

quit

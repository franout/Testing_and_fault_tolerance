set search_path {..}

uplevel #0 source "$LIB_PATH"/pdt2002.dc_setup.tcl

analyze -library work -format vhdl "$CIRCUIT"_"$ARCH".vhd
elaborate "$EXE_N"
#create_clock -name "clk" -period 200 -waveform { 100 200 } { clk }
#create_clock -name "rst" -period 200 -waveform { 100 200 } { rst }

#compile -exact_map
compile_ultra

report_design
report_area -nosplit
#report_clock -nosplit

write -hierarchy -format verilog -output ../"$EXE_N"_synth.v
write -hierarchy -format vhdl -output ../"$EXE_N"_synth.vhd

quit

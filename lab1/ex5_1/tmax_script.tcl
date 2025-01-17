read_netlist ../../library/pdt2002.v -format verilog -insensitive -library
read_netlist ../circ1_struct.vhd -format vhdl -insensitive
run_build_model circ1
run_drc
set_faults -equiv_code --
set_faults -model stuck
add_faults -all
write_faults fault_list_stuckat_full.txt -all -replace -uncollapsed
write_faults fault_list_stuckat_collapsed.txt -all -replace -collapsed
quit

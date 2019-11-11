read_netlist $env(LIB_PATH)/pdt2002.v -format verilog -insensitive -library
if {   $env(FORMAT) == "v"  } {
set i_format  "verilog"
} else {
set i_format "vhdl"
}

read_netlist ../$env(CIRCUIT)_$env(ARC).$env(FORMAT) -format $i_format -insensitive
run_build_model $env(CIRCUIT)
run_drc
set_faults -equiv_code --
set_faults -model stuck
add_faults -all
write_faults fault_list_stuckat_full.txt -all -replace -uncollapsed
write_faults fault_list_stuckat_collapsed.txt -all -replace -collapsed
quit

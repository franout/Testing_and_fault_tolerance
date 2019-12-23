# Setup
set_environment_viewer -instance_names
set_messages -log tmax.log -replace

## Build
read_netlist ../gate/NangateOpenCellLibrary.tlib -library
read_netlist ../gate/riscv_core.v
run_build_model riscv_core_0_128_1_16_1_1_0_0_0_0_0_0_0_0_0_3_6_15_5_1a110800
add_clocks 1 clk_i
run_drc

set_faults -model transition -fault_coverage -atpg_effectiveness -summary verbose
set_delay -launch system_clock
## IDENTIFY varius functional unit
## ATPG



add_faults -all 
remove_faults ex_stage_i/alu_i
run_atpg -auto_compression

## Reports
write_patterns atpg_patterns.stil -format stil -internal -replace
set_faults -fault_coverage
#report_faults -level {5 100} > report_faults_hierarchy.txt
#report_faults -level {100 1} -verbose > report_faults_verbose.txt
#report_summaries > report_summaries.txt
#write_faults fsim_faults.txt -replace -all

quit

# Setup
set_environment_viewer -instance_names
set_messages -log tmax.log -replace

## Build
read_netlist ../gate/NangateOpenCellLibrary.tlib -library
read_netlist ../gate/riscv_core.v
run_build_model riscv_alu_SHARED_INT_DIV0_FPU0

## DRC

add_pi_constraints 0 operator_i[6]
add_pi_constraints 0 operator_i[5]

run_drc

## ATPG
add_faults -all 
remove_faults /int_div_div_i
run_atpg -auto_compression

## Reports
write_patterns atpg_patterns.stil -format stil -internal -replace
#set_faults -fault_coverage
#report_faults -level {5 100} > report_faults_hierarchy.txt
#report_faults -level {100 1} -verbose > report_faults_verbose.txt
#report_summaries > report_summaries.txt
#write_faults fsim_faults.txt -replace -all

quit

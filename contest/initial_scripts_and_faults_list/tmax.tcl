# Setup
set_environment_viewer -instance_names
set_messages -log tmax.log -replace

## Build and DRC
read_netlist ../gate/NangateOpenCellLibrary.tlib -library
read_netlist ../gate/riscv_core.v
run_build_model riscv_core_0_128_1_16_1_1_0_0_0_0_0_0_0_0_0_3_6_15_5_1a110800
add_clocks 1 clk_i
# from tetramax manual ch.17
# In the system_clock mode, the scan enable signal must be inactive between
# launch and capture, so the add_pi_constraints command (or a constraint in the STIL
# procedure file) must be used to set the scan enable signal to inactive. Otherwise, you might get
# patterns in the system_clock mode with the scan enable signal is switching between
# launch and capture
add_pi_contraints 0 SE
run_drc

## Load and check patterns
set_patterns -external dumpports_gate.evcd.fixed  -sensitive -strobe_period { 10 ns } -strobe_offset { 4 ns } -vcd_clock auto
run_simulation -sequential

## Transition faults
set_faults -model transition -fault_coverage -atpg_effectiveness -summary verbose
#based on fast sequential atpg processi
#The -nopi_changes setting causes all primary inputs to be held constant between launch
#and capture, thus preventing slow-to-transition primary inputs from affecting the transition test.
set_delay -launch system_clock -nopi_changes

set_atpg -capture_cycles 2
## Fault list (select one of the following)

if { $env(CUT)=="exe" } {
#execution stage
read_faults ../initial_faults_exe.txt } else {
#total cpu
read_faults ../initial_faults_cpu.txt

}
## Fault simulation
run_fault_sim -sequential

## Reports
set_faults -fault_coverage
report_faults -level {5 100} > report_faults_hierarchy.txt
if { $env(list_modules)=="y" } {
report_modules -all -summary -verbose > ~/contest/modules_list.txt 
}
report_faults -level {100 1} -verbose > report_faults_verbose.txt
report_summaries > report_summaries.txt
write_faults fsim_faults.txt -replace -all
#quit
#
#
#   
#

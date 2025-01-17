# Setup
set_environment_viewer -instance_names
set_messages -log tmax.log -replace

## Build and DRC
read_netlist ../gate/NangateOpenCellLibrary.tlib -library
read_netlist ../gate/riscv_core.v
run_build_model riscv_core_0_128_1_16_1_1_0_0_0_0_0_0_0_0_0_3_6_15_5_1a110800
add_clocks 1 clk_i

# constraints for testing 
add_pi_constraint 1 fregfile_disable_i
add_pi_constraints  1 clock_en_i	
add_pi_constraints 1 test_en_i

run_drc
#set_atpg -capture_cycle 4 not affect the FC

## Load and check patterns
set_patterns -external dumpports_gate.evcd.fixed  -sensitive -strobe_period { 10 ns } -strobe_offset { 4 ns } -vcd_clock auto
#based on fast sequential atpg processi
#The -nopi_changes setting causes all primary inputs to be held constant between launch
#and capture, thus preventing slow-to-transition primary inputs from affecting the transition test.
set_delay -launch system_clock 
set_delay -nopi_changes

run_simulation -sequential

## Transition faults
set_faults -model transition -fault_coverage -atpg_effectiveness -summary verbose
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


### variable design dependent definition

set library_path "../library/pdt2002.v"
set circuit_path "./b06_scan.v"
set circuit "b06" 
set spf_file_path "./b06_scan.spf"

#read the netlist 
read_netlist $library_path -format verilog  -insensitive -library 
read_netlist $circuit_path -format verilog -insensitive -master

# Elaborate the top-level
run_build_model $circuit


# Run default DRC or use SPF file
run_drc $spf_file_path
#set delay model to los
set_delay -launch_cycle last_shift
##########################
######## test ############
##########################
#Set fault model
set_faults -model transition 
#Create fault list or import it (one of the following)
add_faults -all
add_faults $circuit
#or add_faults -module <module name>
# or reaading faults from file
# read_faults <file name> -add [-force_retain_code] [-maintain_detection]

######################################
## Automatic test pattern generator ##
######################################
#Select internal patterns
set_patterns -internal
#Set ATPG options (check the manual)
set_atpg -analyze_untestable_faults
#For sequential circuits
set_atpg -full_seq_atpg
#Run ATPG
run_atpg -auto_compression




########################
### Report summaries ###
########################
set_faults -summary verbose -fault_coverage 
report_summaries > report_loc_transition_delay_fault.txt
write_patterns b06_los_transition_delay.stil -format stil -internal -replace
report_patterns -internal -chain 1 -all > report_pattern_los.txt


## NOTE 
# MUTUALLY EXLUSIVE FROM EACH OTHER -> MAYBE A WAY TO RESET THE ATPG?
### set delay model to loc
set_delay -launch_cycle system_clock -nopi_changes
set_atpg -capture_cycle 2



run_atpg  -auto_compression
set_faults -summary verbose -fault_coverage 
report_summaries > report_los_no_pis_changes_transition_delay_fault.txt
write_patterns b06_loc_no_pis_changes_transition_delay.stil -format stil -internal -replace
report_patterns -internal -chain 1 -all > report_pattern_loc_no_change_pis.txt


set_delay -launch_cycle system_clock -pi_changes
set_atpg -capture_cycle 2
run_atpg -auto_compression 
set_faults -summary verbose -fault_coverage 
report_summaries > report_los_pis_changes_transition_delay_fault.txt
write_patterns b06_loc_pis_changes_transition_delay.stil -format stil -internal -replace
report_patterns -internal -chain 1 -all > report_pattern_los_change_pis.txt




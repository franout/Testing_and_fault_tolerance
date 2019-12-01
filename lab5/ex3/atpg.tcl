### variable design dependent definition
#read the netlist 
read_netlist $env(LIB_PATH)/pdt2002.v -format verilog  -insensitive -library 
read_netlist $env(circuit)_scan.v -format verilog -insensitive -master

# Elaborate the top-level
run_build_model $env(circuit)


# Run default DRC or use SPF file
run_drc $env(circuit)_scan.spf

puts " check how many non scan ffs"
report_primitives -summary 

puts "\n\n\n"

##########################
########  ATPG ###########
##########################
#Set fault model
set_faults -model stuck
#Create fault list or import it (one of the following)
add_faults -all
add_faults $env(circuit)
#Select internal patterns
set_patterns -internal
#Set ATPG options (check the manual)
set_atpg -analyze_untestable_faults
#For sequential circuits
set_atpg -full_seq_atpg
#Run ATPG
run_atpg -auto_compression


#patterns applied for fault simulation 
write_patterns $env(circuit)_saf_scan_patterns.stil  -format stil -internal -replace

set_patterns -external $env(circuit)_saf_scan_patterns.stil
run_simulation -sequential

########################
### Report summaries ###
########################
set_faults -summary verbose -fault_coverage
report_summaries > summary_saf_report_$env(circuit).txt




reset_state
## transition delay fault with lock on shift
set_faults -model transition
set_delay -launch_cycle last_shift
add_faults -all 
add_faults $env(circuit)
set_patterns -internal 
set_atpg -analyze_untestable_faults
set_atpg -full_seq_atpg
run_atpg -auto_compression 
#patterns applied for fault simulation 
write_patterns $env(circuit)_tdf_los_scan_patterns.stil  -format stil -internal -replace

set_patterns -external $env(circuit)_tdf_los_scan_patterns.stil
run_simulation -sequential


set_faults -summary verbose -fault_coverage
report_summaries > summary_tdf_los_report_$env(circuit).txt




reset_state
## transitio delay fault with lock on capture
set_faults -model transition
set_delay -launch_cycle system_clock -pi_changes
add_faults -all 
add_faults $env(circuit)
set_patterns -internal 
set_atpg -capture_cycle 2
set_atpg -analyze_untestable_faults
set_atpg -full_seq_atpg
run_atpg -auto_compression 

#patterns applied for fault simulation 
write_patterns $env(circuit)_tdf_loc_scan_patterns.stil  -format stil -internal -replace

set_patterns -external $env(circuit)_tdf_loc_scan_patterns.stil
run_simulation -sequential





set_faults -summary verbose -fault_coverage
report_summaries > summary_tdf_loc_report_$env(circuit).txt



quit

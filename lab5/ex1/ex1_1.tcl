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

#report 
report_scan_chains  > ./scan_chains.txt

# for each of the chain it is possible to repoort all the ffs
# position 0 is the closest one to the pinout 
report_scan_cells 1 > ./scan_cells_chains_c0.txt


# check how many non scan ffs
report_primitives -summary > primitives_report.txt

##########################
######## test ############
##########################
#Set fault model
set_faults -model stuck
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
	report_summaries
#Write fault list
	write_faults fault_list_uncollapsed.txt -all -uncollapsed -replace
	
#patterns applied for fault simulation 
write_patterns b06_scan_patterns.stil  -format stil -internal -replace


# analize how patterns are applied on the fault
analyze_faults -stuck 0 U50/I2 -verbose -display > applied_patterns.txt
	quit

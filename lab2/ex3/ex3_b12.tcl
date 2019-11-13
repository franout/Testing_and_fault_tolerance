### variable design dependent definition
set atpg "y"
set sequential "y"


set library_path "../library/pdt2002.v"
set faults_file "./faults_list_no_collapsed.txt"
set circuit_path "./b12.v"
set circuit "b12" 
set clock_present "y"
set spf_file_path "./b12.spf"

set po_mask_list [ list ]
set mask_something_po "n"

set pi_constraint [ list  ] 

set constraint_something_pi "n"
#read the netlist 
read_netlist $library_path -format verilog  -insensitive -library 
read_netlist $circuit_path  -insensitive -master

# Elaborate the top-level
run_build_model $circuit

# drc 
#Add clock/reset signals (not needed if you use an SPF file)
if { $clock_present == "y" } {
	add_clock "0" "clock" 
}
# Add Primary input constraints and output masks if needed

if { $constraint_something_pi == "y" } {

foreach name $pi_constraint {

add_pi_constraints X $name
}
report_primitives -pis
}

if { $mask_something_po=="y" } {
add_po_mask -all
foreach name $po_mask_list {
#add_po_mask $name
remove_po_mask $name
	}
###### mask report 
report_primitives -pos
report_po_masks 
}




# Run default DRC or use SPF file
run_drc $spf_file_path

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


if { $atpg == "y" } { 
######################################
## Automatic test pattern generator ##
######################################
#Select internal patterns
	set_patterns -internal
#Set ATPG options (check the manual)
		set_atpg -analyze_untestable_faults
#For sequential circuits
		if { $sequential== "y" } {
			set_atpg -full_seq_atpg
		}
#Run ATPG
	run_atpg -auto_compression
} else {
#####################
## fault simulation #
#####################
#Read external patterns
	set_patterns -external $spf_file_path
#########################
#Check external patterns#
#########################
# run simulation will run a fault free simulation ( golden model ) 
		if { $sequential == "y" } { 
			run_simulation -sequential
#Run fault simulation
				run_fault_sim -sequential
		} else {
			run_simulation 
				run_fault_sim

		}

}



########################
### Report summaries ###
########################
set_faults -summary verbose -fault_coverage
report_summaries
#Write fault list
write_faults $faults_file -all -uncollapsed -replace
quit

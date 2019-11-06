#!/bin/sh

# Move to the run directory
cd run

# Build the files
vlog ../../library/pdt2002.v 
vcom -2008 -suppress 1141 ../"$circuit" ../ex5_1_tb.vhd 
# Invoke QuestaSim shell and run the TCL script
vsim -c -novopt work.tb_ex_5_1 -do ../simulation_script.tcl -wlf sim.wlf
# Alternative: Invoke QuestaSim GUI
#vsim -novopt work.tb_ex1



CIRCUIT=
LIB_PATH=
EXE_N=
.PHONY: all 

all: atpg simulation synthesis 



simulation:
	cd run
	# Build the files
	vlog ../../library/pdt2002.v 
	vcom -2008 -suppress 1141 ../$(CIRCUIT) ../ex5_1_tb.vhd 
	# Invoke QuestaSim shell and run the TCL script
	vsim -c -novopt work.tb_ex_5_1 -do ../simulation_script.tcl -wlf sim.wlf
	# Alternative: Invoke QuestaSim GUI
	#vsim -novopt work.tb_ex1
synthesis:
	cd run
	# Invoke DesignCompiler and run the TCL script
	dc_shell-xg-t -64 -f ../synthesis_script.tcl

atpg:
	mkdir run 
	cd run
	# Invoke TetraMAX and run the TCL script	
	tmax -shell ../tmax_script.tcl

clear:
	rm -rf ./run 
	rm -rf ./work
#!/bin/sh
mkdir run
echo "" > ./run/inject_fault.tcl
./tmax.sh

#producing fault list ( collapsed and full )

circuit="circ1_beh.vhd"
export circuit
# simulatin the fault free circuit 
./simulation.sh
mv ./run/monitor.txt ./run/monitor_gold.txt

#injects faults 
 ./fault_injection_campaign.sh

#synthesis 
./synthesis.sh
#synthesis simulation 
circuit="circ1_struct.vhd"
./simulation.sh

diff -y ./run/monitor.txt ./run/monitor_gold.txt

#cleaning up
rm -rf work 
rm -rf run 
#!/bin/bash

i=0
while read $line 
do
 ./convert_faults.sh run/fault_list_stuckat_full.txt $i > run/inject_fault.tcl
let i=$i+1 
./simulation.sh
diff -y ./run/monitor_gold.txt ./run/monitor.txt | less
done < ./run/fault_list_stuckat_full.txt

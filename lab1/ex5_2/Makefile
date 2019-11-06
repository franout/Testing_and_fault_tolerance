CIRCUIT=circ2
LIB_PATH=../../library
EXE_N=ex5_2
.PHONY: test

simulation:
	# Build the files
	cd run \
	vlog $(LIB_PATH)/pdt2002.v \
	vcom -2008 -suppress 1141 ../$(CIRCUIT) ../$(EXE_N)_tb.vhd \
	vsim -c -novopt work.tb_$(EXE_N) -do ../scripts/simulation_script.tcl -wlf sim.wlf

synthesis:
	# Invoke DesignCompiler and run the TCL script
	cd run \
	dc_shell-xg-t -64 -f ../synthesis_script.tcl

atpg:
	mkdir run
	echo "" > ./run/inject_fault.tcl
	cd run \
	tmax -shell ./../scripts/tmax_script.tcl

clear:
	rm -rf ./run 
	rm -rf ./work


test:
	export CIRCUIT
	export LIB_PATH
	export EXE_N
	export ARCH="beh"	
	#producing fault list ( collapsed and full )
	make atpg
	# simulatin the fault free circuit and save golden model 
	make simulation
	mv ./run/monitor.txt ./run/monitor_gold.txt
	export ARCH="struct"
	#injects faults  and check output 
	 make fault_injection_campaign
	
	#synthesis 
	make synthesis
	#synthesis simulation 
	export CIRCUIT=$(EXE_N)_synth.v
	make simulation 
	
	diff -y ./run/monitor.txt ./run/monitor_gold.txt
	make clear
	
fault_injection_campaign:
	i=0 \
	while read $line \
	do \
	 ./scripts/convert_faults.sh run/fault_list_stuckat_full.txt $i > run/inject_fault.tcl \
	let i=$i+1 \
	make simulation \
	diff -y ./run/monitor_gold.txt ./run/monitor.txt | less \
	done < ./run/fault_list_stuckat_full.txt



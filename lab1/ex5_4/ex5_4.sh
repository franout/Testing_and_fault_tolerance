#!/bin/sh
export CIRCUIT=circ4
export LIB_PATH=../../library
export EXE_N=ex5_4
export ARC=beh	
export FORMAT=vhd
#producing fault list ( collapsed and full )
mkdir run
echo "" > ./run/inject_fault.tcl
cd run 
 tmax -shell ./../scripts/tmax_script.tcl


cd ..

# simulatin the fault free circuit and save golden model 


# Build the files
cd run 

vlog "$LIB_PATH"/pdt2002.v 
vcom -2008 -suppress 1141 ./../"$CIRCUIT"_"$ARC".vhd ./../"$EXE_N"_tb.vhd 
vsim -c -novopt work.tb_"$EXE_N" -do ../scripts/simulation_script.tcl -wlf sim.wlf



mv ./monitor.txt ./monitor_gold.txt
cd ..
export ARC="struct"
#injects faults  and check output 
echo "\n\n######## fault_injection_campaign ##########\n\n"
vcom -2008 -suppress 1141 ./../"$CIRCUIT"_"$ARC".vhd ./../"$EXE_N"_tb.vhd 

i=0 
while read $line
do 
./scripts/convert_faults.sh run/fault_list_stuckat_full.txt $i > run/inject_fault.tcl 
let i=$i+1 
##	make   fault simulation 
cd run 
echo "------------------ injecthed fault --------------------"
cat ./inject_fault.tcl
vsim -c -novopt work.tb_"$EXE_N" -do ../scripts/simulation_script.tcl -wlf sim.wlf
diff -y ./monitor_gold.txt ./monitor.txt 
cd ..
done < ./run/fault_list_stuckat_full.txt
export ARC="beh"	

#synthesis 
# Invoke DesignCompiler and run the TCL script
cd run 
dc_shell-xg-t -64 -f ../scripts/synthesis_script.tcl

cd ..
##echo "\n\n\n -------------- synthesis simulation with injected campaign ---------------\n\n\n"
##
###synthesis simulation with fault injection  
##export ARC="synth"
##export FORMAT="vhd"
##
##echo "" > ./run/inject_fault.tcl
##cd run 
## tmax -shell ./../scripts/tmax_script.tcl
##
##
##cd ..
##
##
##cd run 
##echo "\n\n######## fault_injection_campaign ##########\n\n"
##
##vcom -2008 -suppress 1141 ../"$CIRCUIT"_"$ARC"."$FORMAT" ../"$EXE_N"_tb.vhd 
##cd ..
##i=0 
##while read $line
##do 
##./scripts/convert_faults.sh run/fault_list_stuckat_full.txt $i > run/inject_fault.tcl 
##let i=$i+1 
####	make   fault simulation 
##cd run 
##echo "------------------ injecthed fault --------------------"
##cat ./inject_fault.tcl
##vsim -c -novopt work.tb_"$EXE_N" -do ../scripts/simulation_script.tcl -wlf sim.wlf
##diff -y ./monitor_gold.txt ./monitor.txt 
##cd ..
##done < ./run/fault_list_stuckat_full.txt
##

#clear

rm -rf ./run 
rm -rf ./work
rm -f "$CIRCUIT"_synth*


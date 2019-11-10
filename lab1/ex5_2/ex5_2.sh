#!/bin/sh



export CIRCUIT=circ2
export LIB_PATH=../../library
export EXE_N=ex5_2
export ARC=beh	
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
vcom -2008 -suppress 1141 ../"$CIRCUIT"_"$ARC" ../"$EXE_N"_tb.vhd 
vsim -c -novopt work.cfg_tb_"$EXE_N" -do ../scripts/simulation_script.tcl -wlf sim.wlf



mv ./run/monitor.txt ./run/monitor_gold.txt
cd ..

export ARC="struct"
#injects faults  and check output 
echo "######## fault_injection_campaign ##########"
i=0 
while read $line
do 
./scripts/convert_faults.sh run/fault_list_stuckat_full.txt $i > run/inject_fault.tcl 
let i=$i+1 
##	make   fault simulation 
cd run 
echo "injecthed fault:"
cat ./inject_fault.tcl
vlog "$LIB_PATH"/pdt2002.v 
vcom -2008 -suppress 1141 ../"$CIRCUIT"_"$ARC" ../"$EXE_N"_tb.vhd 
vsim -c -novopt work.tb_"$EXE_N" -do ../scripts/simulation_script.tcl -wlf sim.wlf

cd ..

diff -y ./run/monitor_gold.txt ./run/monitor.txt
done < ./run/fault_list_stuckat_full.txt
#synthesis 
# Invoke DesignCompiler and run the TCL script
cd run 
dc_shell-xg-t -64 -f ../scripts/synthesis_script.tcl

cd ..
#synthesis simulation 
export CIRCUIT="$EXE_N"_synth.v
cd run 
vlog "$LIB_PATH"/pdt2002.v 
vcom -2008 -suppress 1141 ../"$CIRCUIT" ../"$EXE_N"_tb.vhd 
vsim -c -novopt work.tb_"$EXE_N" -do ../scripts/simulation_script.tcl -wlf sim.wlf


diff -y ./run/monitor.txt ./run/monitor_gold.txt
cd ..
#clear

rm -rf ./run 
rm -rf ./work



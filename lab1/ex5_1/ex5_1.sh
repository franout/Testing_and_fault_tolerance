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

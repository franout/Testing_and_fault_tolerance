#!/bin/bash


#producing fault list ( collapsed and full )
./tmax.sh

circuit="ex5_1_beh.vhd"
# simulatin the fault free circuit 
./simulation.sh
mv ./run/monitor.txt ./run/monitor_gold.txt

#injects faults 
 ./fault_injection_campaign.sh

#synthesis 
./synthesis.sh
#synthesis simulation 
circuit="ex5_1_struc.vhd"
./simulation.sh

diff -y ./run/monitor.txt ./run/monitor_gold.txt

#cleaning up
rm -rf work 
rm -rf run 
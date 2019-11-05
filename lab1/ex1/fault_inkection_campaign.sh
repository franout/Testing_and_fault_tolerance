#!/bin/bash

i=0
while read $line 
do
 ./convert_faults.sh run/fault_list_stuckat_full.txt $i > run/inject_fault.tcl
let i=$i+1 
./simulation.sh
diff -y ./run/monitor_gold.txt ./run/monitor.txt | less
done < ./run/fault_list_stuckat_full.txt

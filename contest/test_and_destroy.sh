#!/bin/sh

PATH_CORE="${HOME}/riscv_testing/"
export CUT="exe"
export list_modules="n"

############

cp ./initial_scripts_and_faults_list/tmax.tcl $PATH_CORE/tmax.tcl
#preparing tb
"$PATH_CORE"compile_testbench.sh

mv ./main.c ~/riscv_testing/sbst_c/main.c
# compiling source file in eVCD extendent value change dump
"$PATH_CORE"compile_sbst_c.sh sbst_c/main.c

#move back data
mv ~/riscv_testing/sbst_c/main.c ./main.c


# run simulation logic
# it records the values of PIs and POs
"$PATH_CORE"run_gate_nogui.sh sbst_c/sbst.hex

# run fault simulation
 "$PATH_CORE"run_fsim.sh 


# clean up the mess 
"$PATH_CORE"clean_all.sh



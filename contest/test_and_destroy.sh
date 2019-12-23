#!/bin/sh

PATH_CORE="${HOME}/riscv_testing/"
export CUT="exe"


#preparing tb
"$PATH_CORE"compile_testbench.sh

# if not exists create automatically a list of instruction for the faults throught the ATPG
##if [ ! -f ./atpg_patterns.S ]; then
## 
##./create_atpg_patterns/run_atpg.sh
##./create_atpg_patterns/run_parser.sh
##
##fi
##exit
#####move data
##mv ./atpg_patterns.S ~/riscv_testing/sbst_c/atpg_patterns.S
mv ./main.c ~/riscv_testing/sbst_c/main.c
# compiling source file in eVCD extendent value change dump
"$PATH_CORE"compile_sbst_c.sh sbst_c/main.c

#move back data
#mv ~/riscv_testing/sbst_c/atpg_patterns.S ./atpg_patterns.S
mv ~/riscv_testing/sbst_c/main.c ./main.c


# run simulation logic
# it records the values of PIs and POs
"$PATH_CORE"run_gate_nogui.sh sbst_c/sbst.hex

# run fault simulation
 "$PATH_CORE"run_fsim.sh 


# clean up the mess 
"$PATH_CORE"clean_all.sh



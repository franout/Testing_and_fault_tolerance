#!/bin/sh

PATH_CORE="./../../riscv_testing/"
PATH_SBST="./"
#preparing tb
"$PATH_CORE"compile_testbench.sh

./run_atpg.sh
./run_parser.sh

mv ./atpg_patterns.S ~/riscv_testing/sbst_asm/atpg_pattern.S
# compiling source file in eVCD extendent value change dumo
"$PATH_CORE"compile_sbst_asm.sh "$PATH_SBST"main.S


# run simulation logic
# it records the values of PIs and POs
"$PATH_CORE"run_gate_nogui.sh sbst_asm/sbst.hex

# run fault simulation
 "$PATH_CORE"run_fsim.sh 

# clean up the mess 
"$PATH_CORE"clean_all.sh



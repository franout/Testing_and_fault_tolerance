#|/bin/sh

PATH_CORE="./../riscv_testing/"
PATH_SBST="./"
#preparing tb
"$PATH_CORE"compile_testbench.sh

# compiling source file in eVCD extendent value change dumo
"$PATH_CORE"compile_sbst_c.sh "$PATH_SBST"main.c

# run simulation logic
# it records the values of PIs and POs
"$PATH_CORE"run_gate_nogui.sh "$PATH_CORE"sbst_c/sbst.hex

# run fault simulation
 "$PATH_CORE"run_fsim.sh 


# clean up the mess 
"$PATH_CORE"clean_all.sh

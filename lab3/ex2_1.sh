#|/bin/sh

./../riscv_testing/compile_sbst_c.sh ./ex2_2.c

./../riscv_testing/run_gate_nogui.sh sbst_c/sbst.hex
 ./../riscv_teting/run_fsim.sh

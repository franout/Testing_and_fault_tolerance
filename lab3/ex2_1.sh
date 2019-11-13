#|/bin/sh

./compile_sbst_c.sh ./sbst_c/main.c

./run_gate_nogui.sh sbst_c/sbst.hex
 ./run_fsim.sh

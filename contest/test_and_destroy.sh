#!/bin/sh

PATH_CORE="${HOME}/riscv_testing/"
#######################################################################
##### full -> entire core , exe -> execution stage of the core ########
#######################################################################
export CUT="full"
export list_modules="n"

############
# if cut is the full core modify the main.c

regexp='#define TEST_CORE.*' ; 
	 while  read -r line ; 
	do 
	if [[  $line =~ $regexp  ]] ; then 
			if [ $CUT == "full" ] ; then			
			echo "#define TEST_CORE 1 " >> .tmp_main.c 
			else
			echo "#define TEST_CORE 0 " >> .tmp_main.c 
			fi 
	 	else 
		echo "$line" >> .tmp_main.c ; 
	       	fi  
	       done < main.c
mv .tmp_main.c ./main.c
rm -rf .tmp_main.c

cp ./initial_scripts_and_faults_list/tmax.tcl $PATH_CORE/tmax.tcl
cp ./initial_scripts_and_faults_list/initial_faults_exe.txt $PATH_CORE/initial_faults_exe.txt
cp ./initial_scripts_and_faults_list/initial_faults_cpu.txt $PATH_CORE/initial_faults_cpu.txt
#preparing tb
"$PATH_CORE"compile_testbench.sh

mv ./main.c ~/riscv_testing/sbst_c/main.c
cp ./vectors.S ~/riscv_testing/sbst_c/vectors.S
cp ./atpg_patterns.S ~/riscv_testing/sbst_c/atpg_patterns.S
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



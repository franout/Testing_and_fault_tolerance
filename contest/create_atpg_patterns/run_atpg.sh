#!/bin/bash

cp ./tmax_automatic_patterns.tcl ~/riscv_testing/

cd $(dirname $0)
root_dir=${PWD}
cd - &>/dev/null

run_dir=${root_dir}/../../riscv_testing/run

cd ${run_dir}

tmax -shell ${root_dir}/tmax_automatic_patterns.tcl
cp ${run_dir}/atpg_patterns.stil ${root_dir}/atpg_patterns.stil

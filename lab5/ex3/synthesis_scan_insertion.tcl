uplevel #0 source ../library/pdt2002.dc_setup.tcl

read_verilog $env(file)
current_design $env(circuit)
link
check_design

report_area

set test_default_scan_style multiplexed_flip_flop

create_test_protocol -infer_asynch -infer_clock

dft_drc

## adding 3 scan chain
set_scan_configuration -chain_count  $env(num_sc)
preview_dft
insert_dft
dft_drc

report_scan_path -view existing -chain all
report_scan_path -view existing -cell all

report_area

write -hierarchy -format verilog -output $env(circuit)_scan.v
write_test_protocol -output $env(circuit)_scan.spf

quit

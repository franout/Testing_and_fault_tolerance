uplevel #0 source pdt2002.dc_setup.tcl

read_verilog b10.v
current_design b10
link
check_design

report_area

set test_default_scan_style multiplexed_flip_flop

create_test_protocol -infer_asynch -infer_clock

dft_drc

set_scan_configuration -chain_count 1
preview_dft
insert_dft
dft_drc

report_scan_path -view existing -chain all
report_scan_path -view existing -cell all

report_area

write -hierarchy -format verilog -output b10_scan.v
write_test_protocol -output b10_scan.spf

quit

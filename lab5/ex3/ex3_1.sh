#!/usr/bin/bash

export LIB_PATH="../library"

############################################# 
## scan inserion done by design compiler ####
#############################################
synthesis_script="./synthesis_scan_insertion.tcl"
export file="./b10.v"
export circuit="b10"
dc_shell-xg-t -64 -f $synthesis_script

export file="./b12.v"
export circuit="b12"
dc_shell-xg-t -64 -f $synthesis_script

###########
## atpg ###
###########


export file="./b10.v"
export circuit="b10"
tmax -shell ./atpg.tcl
export file="./b12.v"
export circuit="b12"
tmax -shell ./atpg.tcl



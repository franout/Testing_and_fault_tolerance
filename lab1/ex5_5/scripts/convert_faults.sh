#!/bin/sh

infile=$1
line=$2

head -$line $infile | tail -1 | awk '
/^sa[01]/ { print "force -freeze /cut/" $3, $1 == "sa0" ? "0" : "1" }
'

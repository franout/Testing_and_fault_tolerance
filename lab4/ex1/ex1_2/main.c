#include <stdio.h>
#include <stdlib.h>

/*The ALU can be tested by properly executing arithmetic and logic operations with suitable values.
 * The final program can be composed by several implementation of the following template,
 * in which a generic 3-register instruction ALU_OP is used:
 * 2
 * Write VALUEA in REGA
 * Write VALUEB in REGB
 * ALU_OP (dest: REGC, op1: REGA, op2: REGB)
 * Store REGC in memory
 * ALU_OP (dest: REGC, op1: REGB, op2: REGA)
 * Store REGC in memory
 * ALU_OP: addition, subtraction, bitwise AND, bitwise OR, bitwise XOR…
 * Try to use the same patterns used for the register file also for the ALU.*/


int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}

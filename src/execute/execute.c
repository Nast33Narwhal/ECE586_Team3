/**
 * @file execute.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author TODO
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include "execute.h"

void executeInstruction(instruction_t decInstruction)
{
	switch(decInstruction.instruction)
	{
		case ERROR:
			Fprintf(stderr, "Error: Executing Instruction with ERROR type instruction.\n");
			break;
		case LUI:
			
			break;
		case AUIPC:
			
			break;
		case JAL:
			
			break;
		case JALR:
			
			break;
		case BEQ:

			break;
		case BNE:

			break;
		case BLT:

			break;
		case BGE:

			break;
		case BLTU:

			break;
		case BGEU:

			break;
		case LB:

			break;
		case LH:

			break;
		case LW:

			break;
		case LBU:

			break;
		case LHU:

			break;
		case SB:

			break;
		case SH:

			break;
		case SW:

			break;
		case ADDI:

			break;
		case SLTI:

			break;
		case SLTIU:

			break;
		case XORI:

			break;
		case ORI:

			break;
		case ANDI:
		
			break;
		case SLLI:

			break;
		case SRLI:

			break;
		case SRAI:

			break;
		case ADD:
			addInstruction(decInstruction);
			break;
		case SUB:

			break;
		case SLL:

			break;
		case SLT:

			break;
		case SLTU:

			break;
		case XOR:

			break;
		case SRL:

			break;
		case SRA:

			break;
		case OR:

			break;
		case AND:

			break;
		case ECALL:

			break;
		case EBREAK:

			break;
		default:
			Fprintf(stderr, "Error: Executing Instruction with no valid type instruction.\n");
			break;
	}
}

void addInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// Overflow ignored, rd = rs1 + rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] + REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 + rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1]+ REG[decInstruction.rs2]);
	#endif
}

/**
 * @file execute.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author Drew Seidel (dseidel@pdx.edu)
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
			subInstruction(decInstruction);
			break;
		case SLL:
			sllInstruction(decInstruction);
			break;
		case SLT:
			sltInstruction(decInstruction); 
			break;
		case SLTU:
			sltuInstruction(decInstruction); 
			break;
		case XOR:
			xorInstruction(decInstruction);
			break;
		case SRL:
			srlInstruction(decInstruction);
			break;
		case SRA:
			sraInstruction(decInstruction);
			break;
		case OR:
			orInstruction(decInstruction); 
			break;
		case AND:
			andInstruction(decInstruction);
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

void subInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// Overflow ignored, rd = rs1 - rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] - REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 - rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1]+ REG[decInstruction.rs2]);
	#endif
}

void andInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	//rd = rs1 & rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] & REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 & rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1]+ REG[decInstruction.rs2]);
	#endif
}

void orInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// rd = rs1 | rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] | REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 | rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1]+ REG[decInstruction.rs2]);
	#endif
}

void xorInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	//rd = rs1 ^ rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] ^ REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 ^ rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1]+ REG[decInstruction.rs2]);
	#endif
}

void sltInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	//SLT instruction	
	 if (REG[decInstruction.rs1] < REG[decInstruction.rs2])
	 	 REG[decInstruction.rd] = 1; 
	 else
	 	REG[decInstruction.rd] = 0; 
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %d, rs2 = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2]);
	#endif
}

void sltuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	 //SLTU instruction. NOTE TEST SLTU rd, x0, rs2 sets rd to 1 if rs2 is not equal to 0
	 if ((unsigned int)REG[decInstruction.rs1] < (unsigned int) REG[decInstruction.rs2])
	 	 REG[decInstruction.rd] = 1; 
	 else
	 	 REG[decInstruction.rd] = 0; 
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %d, rs2 = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2]);
	#endif
}

void sllInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	//SLL instruction
	 REG[decInstruction.rd] = REG[decInstruction.rs1] << (REG[decInstruction.rs2] & 0x1F);
	
	#ifdef DEBUG
		Printf("SLL, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
}


void srlInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	
	 REG[decInstruction.rd] = REG[decInstruction.rs1] >> (REG[decInstruction.rs2] & 0x1F);
	
	#ifdef DEBUG
		Printf("SRL, rd = %d, rs1 = %d, rs2 = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2]);
	#endif
}


//todo look into more
void sraInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	REG[decInstruction.rd] = REG[decInstruction.rs1] >>= (REG[decInstruction.rs2] & 0x1F);
	
	#ifdef DEBUG
		Printf("SRA, rd = %d, rs1 = %d, rs2 = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2]);
	#endif
}
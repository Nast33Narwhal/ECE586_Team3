/**
 * @file execute_R.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail R type format instructions for RISC-V ISA
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author Drew Seidel (dseidel@pdx.edu)
 * @author Stephen Short (steshort@pdx.edu)
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include "execute.h"
#include "../registers/registers.h"

// R Type Instructions
void addInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 + rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] + REG[decInstruction.rs2]);
	#endif
	
	// Overflow ignored, rd = rs1 + rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] + REG[decInstruction.rs2]);
	
}

void subInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Sub Instruction, rd = rs1 - rs2 = %d - %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] - REG[decInstruction.rs2]);
	#endif
	
	// Overflow ignored, rd = rs1 - rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] - REG[decInstruction.rs2]);
}

void andInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("And Instruction, rd = rs1 & rs2 = %d & %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] & REG[decInstruction.rs2]);
	#endif
	
	//rd = rs1 & rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] & REG[decInstruction.rs2]);
}

void orInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Or Instruction, rd = rs1 | rs2 = %d | %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] | REG[decInstruction.rs2]);
	#endif
	
	// rd = rs1 | rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] | REG[decInstruction.rs2]);
}

void xorInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Xor Instruction, rd = rs1 ^ rs2 = %d ^ %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] ^ REG[decInstruction.rs2]);
	#endif
	
	//rd = rs1 ^ rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] ^ REG[decInstruction.rs2]);
}

void sltInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %d, rs2 = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2]);
	#endif
	
	//SLT instruction	
	if (REG[decInstruction.rs1] < REG[decInstruction.rs2])
	 	registers_write(decInstruction.rd, 1); 
	else
	 	registers_write(decInstruction.rd, 0); 
}

void sltuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %u, rs2 = %u\n", REG[decInstruction.rd], (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2]);
	#endif
	
	//SLTU instruction. NOTE TEST SLTU rd, x0, rs2 sets rd to 1 if rs2 is not equal to 0
	if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t) REG[decInstruction.rs2]))
		registers_write(decInstruction.rd, 1);
	else
		registers_write(decInstruction.rd, 0);
}

void sllInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SLL, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
	
	//SLL instruction
	registers_write(decInstruction.rd, REG[decInstruction.rs1] << (REG[decInstruction.rs2] & 0x1F));
}


void srlInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SRL, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
	
	registers_write(decInstruction.rd, (uint32_t)REG[decInstruction.rs1] >> (uint32_t)(REG[decInstruction.rs2] & 0x1F));
}


//todo look into more
void sraInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	int32_t msb = REG[decInstruction.rs1] & 0x80000000; // filter out all but msb
	uint32_t shamt = REG[decInstruction.rs2] & 0x1F;
	
	#ifdef DEBUG
		Printf("SRA, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], shamt);
	#endif
	
	if (msb > 0)
	{
		registers_write(decInstruction.rd, signExtend((decInstruction.rs1 >> shamt), 32-shamt));

	}
	else
	{
		registers_write(decInstruction.rd, REG[decInstruction.rs1] >> shamt);
	}
}
// END R Type Instructions

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
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include "execute.h"

// R Type Instructions
void addInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	// Overflow ignored, rd = rs1 + rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] + REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 + rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] + REG[decInstruction.rs2]);
	#endif
}

void subInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	// Overflow ignored, rd = rs1 - rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] - REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Sub Instruction, rd = rs1 - rs2 = %d - %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] - REG[decInstruction.rs2]);
	#endif
}

void andInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	//rd = rs1 & rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] & REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("And Instruction, rd = rs1 & rs2 = %d & %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] & REG[decInstruction.rs2]);
	#endif
}

void orInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	// rd = rs1 | rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] | REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Or Instruction, rd = rs1 | rs2 = %d | %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] | REG[decInstruction.rs2]);
	#endif
}

void xorInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	//rd = rs1 ^ rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] ^ REG[decInstruction.rs2];
	#ifdef DEBUG
		Printf("Xor Instruction, rd = rs1 ^ rs2 = %d ^ %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] ^ REG[decInstruction.rs2]);
	#endif
}

void sltInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}

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
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	//SLTU instruction. NOTE TEST SLTU rd, x0, rs2 sets rd to 1 if rs2 is not equal to 0
	if ((REG[decInstruction.rs1] == 0) && (REG[decInstruction.rs2] != 0))
	{
		REG[decInstruction.rd] = 1;
	}
	else
	{
		if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t) REG[decInstruction.rs2]))
			REG[decInstruction.rd] = 1;
		else
			REG[decInstruction.rd] = 0;
	}
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %u, rs2 = %u\n", REG[decInstruction.rd], (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2]);
	#endif
}

void sllInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	//SLL instruction
	REG[decInstruction.rd] = REG[decInstruction.rs1] << (REG[decInstruction.rs2] & 0x1F);
	
	#ifdef DEBUG
		Printf("SLL, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
}


void srlInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	REG[decInstruction.rd] = REG[decInstruction.rs1] >> (REG[decInstruction.rs2] & 0x1F);
	
	#ifdef DEBUG
		Printf("SRL, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
}


//todo look into more
void sraInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t msb = REG[decInstruction.rs1] & 0x80000000; // filter out all but msb
	uint32_t shamt = REG[decInstruction.rs2] & 0x1F;
	int32_t result = REG[decInstruction.rs1];
	if (msb > 0)
	{
		for (uint32_t i = 0; i != shamt; i++)
		{
			result = (result >> 1) | msb; // Shift once and OR in the 1 to the MSB
		}
		REG[decInstruction.rd] = result;
	}
	else
	{
		REG[decInstruction.rd] = REG[decInstruction.rs1] >> (REG[decInstruction.rs2] & 0x1F);
	}
	#ifdef DEBUG
		Printf("SRA, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
}
// END R Type Instructions

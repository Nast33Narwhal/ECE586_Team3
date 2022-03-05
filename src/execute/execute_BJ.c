/**
 * @file execute.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail B and J format instructions for RISC-V ISA
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

// B Type Instructions
void beqInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	extern uint32_t PC;
	
	int32_t extendedOffset = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedOffset &0x00000800;
	if (msb > 0)
	{
		extendedOffset = extendedOffset | 0xFFFFF000;
	}
	
	if (REG[decInstruction.rs1] == REG[decInstruction.rs2])
	{
		PC = PC + extendedOffset - 4;
	}
	
	#ifdef DEBUG
		Printf("beq Instruction, if (rs1 == rs2) PC = PC + signExtend(offset) - 4 = %u + %d - 4\n", PC, extendedOffset);
	#endif
}

void bneInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	extern uint32_t PC;
	
	int32_t extendedOffset = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedOffset &0x00000800;
	if (msb > 0)
	{
		extendedOffset = extendedOffset | 0xFFFFF000;
	}
	
	if (REG[decInstruction.rs1] != REG[decInstruction.rs2])
	{
		PC = PC + extendedOffset - 4;
	}
	
	#ifdef DEBUG
		Printf("bne Instruction, if (rs1 != rs2) PC = PC + signExtend(offset) - 4 = %u + %d - 4\n", PC, extendedOffset);
	#endif
}

void bltInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	extern uint32_t PC;
	
	int32_t extendedOffset = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedOffset &0x00000800;
	if (msb > 0)
	{
		extendedOffset = extendedOffset | 0xFFFFF000;
	}
	
	if (REG[decInstruction.rs1] < REG[decInstruction.rs2])
	{
		PC = PC + extendedOffset - 4;
	}
	
	#ifdef DEBUG
		Printf("blt Instruction, if (rs1 < rs2) PC = PC + signExtend(offset) - 4 = %u + %d - 4\n", PC, extendedOffset);
	#endif
}

void bgeInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	extern uint32_t PC;
	
	int32_t extendedOffset = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedOffset &0x00000800;
	if (msb > 0)
	{
		extendedOffset = extendedOffset | 0xFFFFF000;
	}
	
	if (REG[decInstruction.rs1] >= REG[decInstruction.rs2])
	{
		PC = PC + extendedOffset - 4;
	}
	
	#ifdef DEBUG
		Printf("bge Instruction, if (rs1 >= rs2) PC = PC + signExtend(offset) - 4 = %u + %d - 4\n", PC, extendedOffset);
	#endif
}

void bltuInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	extern uint32_t PC;
	
	int32_t extendedOffset = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedOffset &0x00000800;
	if (msb > 0)
	{
		extendedOffset = extendedOffset | 0xFFFFF000;
	}
	
	if (((unsigned) REG[decInstruction.rs1]) < ((unsigned) REG[decInstruction.rs2]))
	{
		PC = PC + extendedOffset - 4;
	}
	
	#ifdef DEBUG
		Printf("bltu Instruction, if (((unsigned) rs1) < ((unsigned) rs2)) PC = PC + signExtend(offset) - 4 = %u + %d - 4\n", PC, extendedOffset);
	#endif
}

void bgeuInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	extern uint32_t PC;
	
	int32_t extendedOffset = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedOffset &0x00000800;
	if (msb > 0)
	{
		extendedOffset = extendedOffset | 0xFFFFF000;
	}
	
	if (((unsigned) REG[decInstruction.rs1]) >= ((unsigned) REG[decInstruction.rs2]))
	{
		PC = PC + extendedOffset - 4;
	}
	
	#ifdef DEBUG
		Printf("bgeu Instruction, if (((unsigned) rs1) >= ((unsigned) rs2)) PC = PC + signExtend(offset) - 4 = %u + %d - 4\n", PC, extendedOffset);
	#endif
}
// END B Type Instructions

// J Type Instructions
void jalInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	extern uint32_t PC;
	
	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	// Set least significant bit to 0 per spec
	extendedImmediate = extendedImmediate & 0xFFFFFFFE; 
	
	// Check for 4 byte alignment
	uint32_t destination = (uint32_t) (REG[decInstruction.rs1] + extendedImmediate);
	if ((destination & 0x3) != 0)
	{
		Fprintf(stderr, "Error: jalInstruction has a destination for the PC which is not 4-byte aligned\n");
	}
	
	// if rd = reg[0], don't store anything, but still change PC.
	if (decInstruction.rd == 0)
	{
		PC = ((uint32_t) (REG[decInstruction.rs1] + extendedImmediate)) - 4;
	}
	else
	{
		REG[decInstruction.rd] = PC + 4;
		PC = ((uint32_t) (REG[decInstruction.rs1] + extendedImmediate)) - 4;
	}
	#ifdef DEBUG
		Printf("JAL, rd = %d, signExtend(imm) = %d, PC = %u\n", REG[decInstruction.rd], extendedImmediate, PC);
	#endif
}
// END J Type Instructions

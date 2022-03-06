/**
 * @file execute.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail I format instructions for the RISC-V ISA
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

// I Type Instructions
void lbInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			memoryLoaded = (memoryLoaded & 0x000000FF);
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0x0000FF00) >>  8;
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0x00FF0000) >> 16;
			break;
		case 3:
			memoryLoaded = (memoryLoaded & 0xFF000000) >> 24;
			break;
		default:
			Fprintf(stderr, "Error executing LB Instruction, byte select error\n");
			exit(1);
	}

	// Sign extend
	int32_t msb = memoryLoaded &0x00000080;
	if (msb > 0) // Need to sign extend
	{
		memoryLoaded = memoryLoaded | 0xFFFFFF00; // Sign extend
	}

	registers_write(decInstruction.rd, memoryLoaded);

	#ifdef DEBUG
		Printf("LB, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lhInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			memoryLoaded = (memoryLoaded & 0x0000FFFF);
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0x00FFFF00) >>  8;
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0xFFFF0000) >> 16;
			break;
		case 3: // Happens on a boundary, need to grab the other 8 bits
			memoryLoaded = ((memoryLoaded & 0xFF000000) >> 24) | ((readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1) & 0x000000FF) << 8);
			break;
		default:
			Fprintf(stderr, "Error executing LH Instruction, byte select error\n");
			exit(1);
	}

	// Sign extend
	int32_t msb = memoryLoaded &0x00008000;
	if (msb > 0) // Need to sign extend
	{
		memoryLoaded = memoryLoaded | 0xFFFF0000; // Sign extend
	}


	registers_write(decInstruction.rd, memoryLoaded);

	#ifdef DEBUG
		Printf("LH, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lwInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			// memoryLoaded already set
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0xFFFFFF00) >>  8 | ((readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1) & 0x000000FF) << 24);
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0xFFFF0000) >> 16 | ((readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1) & 0x0000FFFF) << 16);
			break;
		case 3: // Happens on a boundary, need to grab the other 8 bits
			memoryLoaded = ((memoryLoaded & 0xFF000000) >> 24) | ((readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1) & 0x00FFFFFF) << 8);
			break;
		default:
			Fprintf(stderr, "Error executing LW Instruction, byte select error\n");
			exit(1);
	}

	// Sign extend not needed

	registers_write(decInstruction.rd, memoryLoaded);

	#ifdef DEBUG
		Printf("LW, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lbuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			memoryLoaded = (memoryLoaded & 0x000000FF);
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0x0000FF00) >>  8;
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0x00FF0000) >> 16;
			break;
		case 3:
			memoryLoaded = (memoryLoaded & 0xFF000000) >> 24;
			break;
		default:
			Fprintf(stderr, "Error executing LB Instruction, byte select error\n");
			exit(1);
	}

	// No Sign Extend

	registers_write(decInstruction.rd, memoryLoaded);

	#ifdef DEBUG
		Printf("LBU, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lhuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			memoryLoaded = (memoryLoaded & 0x0000FFFF);
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0x00FFFF00) >>  8;
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0xFFFF0000) >> 16;
			break;
		case 3: // Happens on a boundary, need to grab the other 8 bits
			memoryLoaded = ((memoryLoaded & 0xFF000000) >> 24) | ((readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1) & 0x000000FF) << 8);
			break;
		default:
			Fprintf(stderr, "Error executing LH Instruction, byte select error\n");
			exit(1);
	}

	// No Sign Extend

	registers_write(decInstruction.rd, memoryLoaded);

	#ifdef DEBUG
		Printf("LHU, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void addiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	// Overflow ignored, rd = rs1 + rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] + extendedImmediate);
	#ifdef DEBUG
		Printf("Addi Instruction, rd = rs1 + signExtended(imm) = %d + signExtended(%d) = %d + %d = %d\n", REG[decInstruction.rs1], decInstruction.immediate, REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] + extendedImmediate);
	#endif
}

void slliInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	//shamt is unsigned 5 bit value
	int32_t shamt = decInstruction.immediate & 0x1F;

	// Overflow ignored, rd = rs1 + rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] << shamt);
	#ifdef DEBUG
		Printf("Slli Instruction, rd = rs1 << (imm & 0x1F) = %d << %d = = %d\n", REG[decInstruction.rs1], shamt, REG[decInstruction.rs1] << shamt);
	#endif
}

void sltiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	//SLTI instruction
	if (REG[decInstruction.rs1] < extendedImmediate)
	 	registers_write(decInstruction.rd, 1);
	else
	 	registers_write(decInstruction.rd, 0);

	#ifdef DEBUG
		Printf("SLTI, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], extendedImmediate);
	#endif
}

void sltiuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	//SLTIU instruction. NOTE TEST SLTIU rd, x0, imm sets rd to 1 if rs1 is equal to 0 and imm is equal to 1
	if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t) extendedImmediate))
		registers_write(decInstruction.rd, 1);
	else
		registers_write(decInstruction.rd, 0);

	#ifdef DEBUG
		Printf("SLTIU, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %u\n", REG[decInstruction.rd], REG[decInstruction.rs1], (uint32_t) extendedImmediate);
	#endif
}

void xoriInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	//rd = rs1 ^ signExtend(imm);
	registers_write(decInstruction.rd, REG[decInstruction.rs1] ^ extendedImmediate);
	#ifdef DEBUG
		Printf("Xori Instruction, rd = rs1 ^ signExtended(imm) = %d ^ %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] ^ extendedImmediate);
	#endif
}

void oriInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	// rd = rs1 | rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] | extendedImmediate);
	#ifdef DEBUG
		Printf("Ori Instruction, rd = rs1 | signExtended(imm) = %d | %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] | extendedImmediate);
	#endif
}

void andiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	//rd = rs1 & rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] & extendedImmediate);
	#ifdef DEBUG
		Printf("Andi Instruction, rd = rs1 & signExtended(imm) = %d & %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] & extendedImmediate);
	#endif
}

void srliInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	registers_write(decInstruction.rd, REG[decInstruction.rs1] >> (decInstruction.immediate & 0x1F));

	#ifdef DEBUG
		Printf("SRLI, rd = %d, rs1 = %d, imm & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate & 0x1F);
	#endif
}

//todo look into more
void sraiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t msb = REG[decInstruction.rs1] & 0x80000000; // filter out all but msb
	uint32_t shamt = decInstruction.immediate & 0x1F;
	int32_t result = REG[decInstruction.rs1];
	if (msb > 0)
	{
		for (uint32_t i = 0; i != shamt; i++)
		{
			result = (result >> 1) | msb; // Shift once and OR in the 1 to the MSB
		}
		registers_write(decInstruction.rd, result);
	}
	else
	{
		registers_write(decInstruction.rd, REG[decInstruction.rs1] >> (decInstruction.immediate & 0x1F));
	}
	#ifdef DEBUG
		Printf("SRAI, rd = %d, rs1 = %d, imm & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate & 0x1F);
	#endif
}

void jalrInstruction(instruction_t decInstruction)
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

	// Store return address in rd
	registers_write(decInstruction.rd, PC + 4);
	PC = ((uint32_t) (REG[decInstruction.rs1] + extendedImmediate)) - 4;

	#ifdef DEBUG
		Printf("JALR, rd = %d, rs1 = %d, PC = %u, signExtended(imm) & 0xFFFFFFFC = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], PC, extendedImmediate);
	#endif
}

void ecallInstruction(instruction_t decInstruction)
{
	Printf("ecall instruction not set up yet\n");
}

void ebreakInstruction(instruction_t decInstruction)
{
	Printf("ebreak instruction not set up yet\n");
}

// END I Type Instructions

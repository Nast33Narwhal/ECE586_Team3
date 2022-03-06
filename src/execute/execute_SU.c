/**
 * @file execute.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail S format instructions for the RISC-V ISA
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

// S Type Instructions
void sbInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );
	int32_t byteToStore = REG[decInstruction.rs2];

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			memoryLoaded = (memoryLoaded & 0xFFFFFF00) | byteToStore;
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0xFFFF00FF) | (byteToStore << 8);
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0xFF00FFFF) | (byteToStore << 16);
			break;
		case 3:
			memoryLoaded = (memoryLoaded & 0x00FFFFFF) | (byteToStore << 24);
			break;
		default:
			Fprintf(stderr, "Error executing SB Instruction, byte select error\n");
			exit(1);
	}
	writeMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) , memoryLoaded);

	#ifdef DEBUG
		Printf("SB, rs1 = %d, rs2 = %d, imm = %d", REG[decInstruction.rs1], REG[decInstruction.rs2], decInstruction.immediate);
	#endif
}

void shInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );
	int32_t shortToStore = REG[decInstruction.rs2];

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			memoryLoaded = (memoryLoaded & 0xFFFF0000) | shortToStore;
			writeMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), memoryLoaded);
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0xFF0000FF) | (shortToStore << 8);
			writeMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), memoryLoaded);
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0x0000FFFF) | (shortToStore << 16);
			writeMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), memoryLoaded);
			break;
		case 3: // Happens on a boundary, need to grab the other 8 bits
			memoryLoaded = (memoryLoaded & 0x00FFFFFF) | (shortToStore << 24);
			writeMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), memoryLoaded);
			// Load next word to store other half of short
			memoryLoaded = readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1);
			memoryLoaded = (memoryLoaded & 0xFFFFFF00) | (shortToStore >> 8);
			writeMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) + 1, memoryLoaded);
			break;
		default:
			Fprintf(stderr, "Error executing LH Instruction, byte select error\n");
			exit(1);
	}

	#ifdef DEBUG
		Printf("SH, rs1 = %d, rs2 = %d, imm = %d", REG[decInstruction.rs1], REG[decInstruction.rs2], decInstruction.immediate);
	#endif
}

void swInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load 32 bit value from memory (base + offset)
	int32_t memoryLoaded = readMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) );
	int32_t wordToStore = REG[decInstruction.rs2];

	// Determine byte selected
	int32_t byteSelected = decInstruction.immediate % 4;
	switch(byteSelected)
	{
		case 0:
			// memoryLoaded already set
			writeMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), wordToStore);
			break;
		case 1:
			memoryLoaded = (memoryLoaded & 0x000000FF) | (wordToStore << 8);
			writeMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), memoryLoaded);
			// Load next word to store other byte of the word
			memoryLoaded = readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1);
			memoryLoaded = (memoryLoaded & 0xFFFFFF00) | (wordToStore >> 24);
			writeMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) + 1, memoryLoaded);
			break;
		case 2:
			memoryLoaded = (memoryLoaded & 0x0000FFFF) | (wordToStore << 16);
			writeMemory( (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), memoryLoaded);
			// Load next word to store other byte of the word
			memoryLoaded = readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1);
			memoryLoaded = (memoryLoaded & 0xFFFF0000) | (wordToStore >> 16);
			writeMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) + 1, memoryLoaded);
			break;
		case 3: // Happens on a boundary, need to grab the other 8 bits
			memoryLoaded = (memoryLoaded & 0x00FFFFFF) | (wordToStore << 24);
			writeMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), memoryLoaded);
			// Load next word to store other half of the word
			memoryLoaded = readMemory(((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)) + 1);
			memoryLoaded = (memoryLoaded & 0xFF000000) | (wordToStore >> 8);
			writeMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4) + 1, memoryLoaded);
			break;
		default:
			Fprintf(stderr, "Error executing LH Instruction, byte select error\n");
			exit(1);
	}

	#ifdef DEBUG
		Printf("SW, rs1 = %d, rs2 = %d, imm = %d", REG[decInstruction.rs1], REG[decInstruction.rs2], decInstruction.immediate);
	#endif
}
// END S Type Instructions

// U Type Instructions
void auipcInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	extern uint32_t PC;

	registers_write(decInstruction.rd, PC + decInstruction.immediate);
	#ifdef DEBUG
		Printf("auipc Instruction, rd = pc + immediate = %d + %d = %d\n", PC, decInstruction.immediate, PC + decInstruction.immediate);
	#endif
}

void luiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	registers_write(decInstruction.rd, decInstruction.immediate);
	#ifdef DEBUG
		Printf("lui Instruction, rd = immediate = %d\n", decInstruction.immediate);
	#endif
}
// END U Type Instructions

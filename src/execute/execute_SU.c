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

	int32_t byteToStore = REG[decInstruction.rs2] & 0xFF; //Grab lowest byte from source register
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11)); //Calculate address
	uint8_t byteOffset = address % 4; //Calculate byte offset
	writeMemoryMasked(address/4, byteToStore<<(byteOffset*8), 0xFF<<(byteOffset*8)); //Overwrite byte in memory

	#ifdef DEBUG
		Printf("SB, rs1 = %u, rs2 = %u, imm = %d", REG[decInstruction.rs1], REG[decInstruction.rs2], signExtend(decInstruction.immediate,11));
	#endif
}

void shInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t shortToStore = REG[decInstruction.rs2] & 0xFFFF;
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11));
	uint8_t byteOffset = address % 4;
	writeMemoryMasked(address/4, shortToStore<<(byteOffset*8), 0xFFFF<<(byteOffset*8));
	if (byteOffset == 3)
		writeMemoryMasked(address/4 + 1, shortToStore >> 8, 0xFF);

	#ifdef DEBUG
		Printf("SH, rs1 = %u, rs2 = %u, imm = %d", REG[decInstruction.rs1], REG[decInstruction.rs2], signExtend(decInstruction.immediate,11));
	#endif
}

void swInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	#ifdef DEBUG
		Printf("SW, rs1 = %u, rs2 = %u, imm = %d", REG[decInstruction.rs1], REG[decInstruction.rs2], signExtend(decInstruction.immediate,11));
	#endif

	int32_t wordToStore = REG[decInstruction.rs2]; //Get value to store
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11)); //Calculate address
	uint8_t byteOffset = address % 4; //Calculate bytes offset from word alignment
	writeMemoryMasked(address/4, wordToStore<<(byteOffset*8), 0xFFFFFFFF<<(byteOffset*8)); //Write word to memory
	if (byteOffset) //If word is not word aligned...
		writeMemoryMasked(address/4 + 1, wordToStore >> (byteOffset * 8), 0xFFFFFFFF >> (byteOffset * 8)); //Write MSBs into next word
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

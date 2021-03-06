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

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate, 11));
	uint8_t byteOffset = address % 4;
	int32_t byteLoaded = (readMemory(address / 4) >> (byteOffset * 8)) & 0xFF;

#ifdef DEBUG
	Printf("LB, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate, 11), signExtend(byteLoaded, 7));
#endif

	registers_write(decInstruction.rd, (uint32_t)signExtend(byteLoaded, 7));
}

void lhInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate, 11));
	uint8_t byteOffset = address % 4;
	int32_t hwLoaded = (readMemory(address / 4) >> (byteOffset * 8)) & 0xFFFF;
	if (byteOffset == 3)
	{
		hwLoaded |= ((readMemory(address / 4 + 1) << 8) & 0xFF00);
	}

#ifdef DEBUG
	Printf("LH, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate, 11), signExtend(hwLoaded, 15));
#endif

	registers_write(decInstruction.rd, (uint32_t)signExtend(hwLoaded, 15));
}

void lwInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate, 11));
	uint8_t byteOffset = address % 4;
	int32_t wordLoaded = (readMemory(address / 4) >> (byteOffset * 8)) & (0xFFFFFFFF >> (byteOffset * 8));
	if (byteOffset != 0)
	{

		wordLoaded |= ((readMemory(address / 4 + 1) << (32 - (byteOffset * 8))) & (0xFFFFFFFF << (32 - byteOffset * 8)));
	}

#ifdef DEBUG
	Printf("LW, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate, 11), wordLoaded);
#endif

	registers_write(decInstruction.rd, (uint32_t)wordLoaded);
}

void lbuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate, 11));
	uint8_t byteOffset = address % 4;
	int32_t byteLoaded = (readMemory(address / 4) >> (byteOffset * 8)) & 0xFF;

#ifdef DEBUG
	Printf("LBU, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate, 11), byteLoaded);
#endif

	registers_write(decInstruction.rd, (uint32_t)byteLoaded);
}

void lhuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate, 11));
	uint8_t byteOffset = address % 4;
	int32_t hwLoaded = (readMemory(address / 4) >> (byteOffset * 8)) & 0xFFFF;
	if (byteOffset == 3)
	{
		hwLoaded |= ((readMemory(address / 4 + 1) << 8) & 0xFF00);
	}
#ifdef DEBUG
	Printf("LHU, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate, 11), hwLoaded);
#endif

	registers_write(decInstruction.rd, (uint32_t)hwLoaded);
}

void addiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate & 0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

#ifdef DEBUG
	if (extendedImmediate == 0)
	{
		Printf("Mv Instruction, rd = rs1 = %d \n", REG[decInstruction.rs1]);
	}
	else
	{
		Printf("Addi Instruction, rd = rs1 + signExtended(imm) = %d + signExtended(%d) = %d + %d = %d\n", REG[decInstruction.rs1], decInstruction.immediate, REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] + extendedImmediate);
	}
#endif

	// Overflow ignored, rd = rs1 + rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] + extendedImmediate);
}

void slliInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// shamt is unsigned 5 bit value
	int32_t shamt = decInstruction.immediate & 0x1F;

#ifdef DEBUG
	Printf("Slli Instruction, rd = rs1 << (imm & 0x1F) = %d << %d = = %d\n", REG[decInstruction.rs1], shamt, REG[decInstruction.rs1] << shamt);
#endif

	// Overflow ignored, rd = rs1 + rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] << shamt);
}

void sltiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate & 0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

#ifdef DEBUG
	Printf("SLTI, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], extendedImmediate);
#endif

	// SLTI instruction
	if (REG[decInstruction.rs1] < extendedImmediate)
		registers_write(decInstruction.rd, 1);
	else
		registers_write(decInstruction.rd, 0);
}

void sltiuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate & 0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

#ifdef DEBUG
	Printf("SLTIU, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %u\n", REG[decInstruction.rd], REG[decInstruction.rs1], (uint32_t)extendedImmediate);
#endif

	// SLTIU instruction. NOTE TEST SLTIU rd, x0, imm sets rd to 1 if rs1 is equal to 0 and imm is equal to 1
	if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t)extendedImmediate))
		registers_write(decInstruction.rd, 1);
	else
		registers_write(decInstruction.rd, 0);
}

void xoriInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate & 0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

#ifdef DEBUG
	Printf("Xori Instruction, rd = rs1 ^ signExtended(imm) = %d ^ %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] ^ extendedImmediate);
#endif

	// rd = rs1 ^ signExtend(imm);
	registers_write(decInstruction.rd, REG[decInstruction.rs1] ^ extendedImmediate);
}

void oriInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate & 0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

#ifdef DEBUG
	Printf("Ori Instruction, rd = rs1 | signExtended(imm) = %d | %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] | extendedImmediate);
#endif

	// rd = rs1 | rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] | extendedImmediate);
}

void andiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate & 0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

#ifdef DEBUG
	Printf("Andi Instruction, rd = rs1 & signExtended(imm) = %d & %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] & extendedImmediate);
#endif

	// rd = rs1 & rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] & extendedImmediate);
}

void srliInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

#ifdef DEBUG
	Printf("SRLI, rd = %d, rs1 = %d, imm & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate & 0x1F);
#endif

	registers_write(decInstruction.rd, (uint32_t)REG[decInstruction.rs1] >> (decInstruction.immediate & 0x1F));
}

// todo look into more
void sraiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int32_t msb = REG[decInstruction.rs1] & 0x80000000; // filter out all but msb
	uint32_t shamt = decInstruction.immediate & 0x1F;

#ifdef DEBUG
	Printf("SRAI, rd = %d, rs1 = %d, shamt = imm & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], shamt);
#endif

	if (msb > 0)
	{
		registers_write(decInstruction.rd, signExtend((REG[decInstruction.rs1] >> shamt), 32 - shamt));
	}
	else
	{
		registers_write(decInstruction.rd, REG[decInstruction.rs1] >> shamt);
	}
}

void jalrInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	extern uint32_t PC;

	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate & 0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	// Set least significant bit to 0 per spec
	extendedImmediate = extendedImmediate & 0xFFFFFFFE;
	
	// Check for unaligned offset
	if ((extendedImmediate & 0x3) > 0)
	{
		Fprintf(stderr, "Error: JALR Instruction's offset is not 4-byte aligned. Correcting and continuing.\n");
		extendedImmediate = extendedImmediate & 0xFFFFFFFC;
	}

#ifdef DEBUG
	Printf("JALR, rd = %d, rs1 = %d, PC = rs1 + signExtend(imm) - 4 = %d + %d - 4 = %u, signExtended(imm) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs1], extendedImmediate, (uint32_t) (REG[decInstruction.rs1] + extendedImmediate - 4));
#endif

	// Store return address in rd
	registers_write(decInstruction.rd, PC + 4);
	PC = ((uint32_t)(REG[decInstruction.rs1] + extendedImmediate)) - 4;
}
void ecallInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	int i = 0;

	int32_t address = REG[11]; // + REG[12] - 1; // address of buffer + string length
	uint8_t byteOffset = address % 4;	 // byte offset;
	int32_t byteLoaded = 0;
	int32_t byteRead = 0;

	switch (REG[17]) // switch a7 for type system call
	{
	case 63:
		if (REG[10] == 0)
		{
			i = address; 
			Printf("Enter String:"); 
			do
			{
				byteRead = getchar();
				writeMemoryMasked(i / 4, byteRead << (byteOffset * 8), 0xFF << (byteOffset * 8)); // Overwrite byte in memory
				i++;
				byteOffset = i % 4;
			} while (byteRead != '\n' && byteRead != '\0' && i < REG[11] + REG[12]);
		}
		else
		{
			Printf("Invalid File Descriptor. Write 0 to a0 for STDIN\n");
		}
		if (i == REG[11]) // add better method of checking completion
		{
			registers_write(10, REG[12]); 
			
		}	 
		else if ((byteRead == '\n' || byteRead == '\0') && i != REG[11])
		{
			 registers_write(10, address - i); 
		}	
		else
		{
			registers_write(10, -1);
		}
		break;
	case 64:
		#ifdef DEBUG
		Printf("ECALL PRINT TO STDOUT MESSAGE:"); 
		#endif
		if (REG[10] == 1) // if a0 = 1, standard out.
		{
			for (i = address; i < REG[11] + REG[12]; i++) // start at high address for little endian
			{
				byteOffset = i % 4; // reset byte offset
				byteLoaded = (readMemory(i / 4) >> (byteOffset * 8)) & 0xFF;
				Fprintf(stdout, "%c", byteLoaded); // print hex as string (? test)
			}
			Printf("\n");
		}
		else
		{
			Printf("Invalid File Descriptor. Write 1 to a0 for STDOUT\n");
		}
		if (i == (REG[11] -1)) // add better method of checking completion
			registers_write(10, REG[12]); 
		else
			registers_write(10, -1);
		break;
	case 94:
		Printf("Exiting due to system call exit\n");
		//printRegisters(); 
		exit(0);
	default:
		Printf("Error, invalid system call type\n");
		exit(1);
	}
	// Printf("ecall instruction not set up yet\n");
}

void ebreakInstruction(instruction_t decInstruction)
{
	Printf("ebreak instruction not set up yet\n");
}

// END I Type Instructions

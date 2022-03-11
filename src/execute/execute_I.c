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
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11));
	uint8_t byteOffset = address % 4;
	int32_t byteLoaded = (readMemory(address/4)>>(byteOffset*8)) & 0xFF;
	
	#ifdef DEBUG
		Printf("LB, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate,11), signExtend(byteLoaded, 7));
	#endif
	
	registers_write(decInstruction.rd, (uint32_t)signExtend(byteLoaded, 7));
}

void lhInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11));
	uint8_t byteOffset = address % 4;
	int32_t hwLoaded = (readMemory(address/4)>>(byteOffset*8)) & 0xFFFF;
	if (byteOffset == 3)
	{
		hwLoaded |= ((readMemory(address/4 + 1) << 8) & 0xFF00);
	}
	
	#ifdef DEBUG
		Printf("LH, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate,11), signExtend(hwLoaded,15));
	#endif
	
	registers_write(decInstruction.rd, (uint32_t)signExtend(hwLoaded, 15));
}

void lwInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11));
	uint8_t byteOffset = address % 4; 
	int32_t wordLoaded = (readMemory(address/4)>>(byteOffset*8)) & (0xFFFFFFFF>>(byteOffset*8));
	if (byteOffset != 0)
	{	
		
		wordLoaded |= ((readMemory(address/4 + 1) << (32-(byteOffset * 8))) & (0xFFFFFFFF<<(byteOffset*8)));
	}
	
	#ifdef DEBUG
		Printf("LW, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate,11), wordLoaded);
	#endif
	
	registers_write(decInstruction.rd, (uint32_t)wordLoaded);
}

void lbuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11));
	uint8_t byteOffset = address % 4;
	int32_t byteLoaded = (readMemory(address/4)>>(byteOffset*8)) & 0xFF;
	
	#ifdef DEBUG
		Printf("LBU, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate,11), byteLoaded<<24);
	#endif
	
	registers_write(decInstruction.rd, (uint32_t)(byteLoaded << 24));
}

void lhuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	// Load value from memory (base + offset)
	unsigned address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11));
	uint8_t byteOffset = address % 4;
	int32_t hwLoaded = (readMemory(address/4)>>(byteOffset*8)) & 0xFFFF;
	if (byteOffset == 3)
	{
		hwLoaded |= ((readMemory(address/4 + 1) << 8) & 0xFF00);
	}
	#ifdef DEBUG
		Printf("LHU, rd = %u, rs1 = %u, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], signExtend(decInstruction.immediate,11), hwLoaded<<16);
	#endif
	
	registers_write(decInstruction.rd, (uint32_t)(hwLoaded << 16));
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

	#ifdef DEBUG
		Printf("Addi Instruction, rd = rs1 + signExtended(imm) = %d + signExtended(%d) = %d + %d = %d\n", REG[decInstruction.rs1], decInstruction.immediate, REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] + extendedImmediate);
	#endif

	// Overflow ignored, rd = rs1 + rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] + extendedImmediate);
	
}

void slliInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	//shamt is unsigned 5 bit value
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
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	#ifdef DEBUG
		Printf("SLTI, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], extendedImmediate);
	#endif
	
	//SLTI instruction
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
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	#ifdef DEBUG
		Printf("SLTIU, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %u\n", REG[decInstruction.rd], REG[decInstruction.rs1], (uint32_t) extendedImmediate);
	#endif

	//SLTIU instruction. NOTE TEST SLTIU rd, x0, imm sets rd to 1 if rs1 is equal to 0 and imm is equal to 1
	if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t) extendedImmediate))
		registers_write(decInstruction.rd, 1);
	else
		registers_write(decInstruction.rd, 0);
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
	
	#ifdef DEBUG
		Printf("Xori Instruction, rd = rs1 ^ signExtended(imm) = %d ^ %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] ^ extendedImmediate);
	#endif
	
	//rd = rs1 ^ signExtend(imm);
	registers_write(decInstruction.rd, REG[decInstruction.rs1] ^ extendedImmediate);
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
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	#ifdef DEBUG
		Printf("Andi Instruction, rd = rs1 & signExtended(imm) = %d & %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] & extendedImmediate);
	#endif
	
	//rd = rs1 & rs2;
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

//todo look into more
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
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	// Set least significant bit to 0 per spec
	extendedImmediate = extendedImmediate & 0xFFFFFFFE;

	#ifdef DEBUG
		Printf("JALR, rd = %d, rs1 = %d, PC = %u, signExtended(imm) & 0xFFFFFFFC = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], PC, extendedImmediate);
	#endif
	
	// Store return address in rd
	registers_write(decInstruction.rd, PC + 4);
	PC = ((uint32_t) (REG[decInstruction.rs1] + extendedImmediate)) - 4;
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

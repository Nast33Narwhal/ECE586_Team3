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
	extern int32_t* REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		#ifdef DEBUG
			Printf("Instruction Execution Requested has rd = x0, do nothing and return.\n");
		#endif
		
		return;
	}
	
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
			lbInstruction(decInstruction);
			break;
		case LH:
			lhInstruction(decInstruction);
			break;
		case LW:
			lwInstruction(decInstruction);
			break;
		case LBU:
			lbuInstruction(decInstruction);
			break;
		case LHU:
			lhuInstruction(decInstruction);
			break;
		case SB:

			break;
		case SH:

			break;
		case SW:

			break;
		case ADDI:
			addiInstruction(decInstruction);
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
			slliInstruction(decInstruction);
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

// R Type Instructions
void addInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
	//SLTU instruction. NOTE TEST SLTU rd, x0, rs2 sets rd to 1 if rs2 is not equal to 0
	if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t) REG[decInstruction.rs2]))
	 	REG[decInstruction.rd] = 1;
	else
	 	REG[decInstruction.rd] = 0;
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %u, rs2 = %u\n", REG[decInstruction.rd], (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2]);
	#endif
}

void sllInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
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
	if (REG[decInstruction.rd] == 0)
	{
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

// I Type Instructions
void lbInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
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

	
	REG[decInstruction.rd] = memoryLoaded;
	
	#ifdef DEBUG
		Printf("LB, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.immediate], memoryLoaded);
	#endif
}

void lhInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
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

	
	REG[decInstruction.rd] = memoryLoaded;
	
	#ifdef DEBUG
		Printf("LH, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.immediate], memoryLoaded);
	#endif
}

void lwInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
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

	REG[decInstruction.rd] = memoryLoaded;
	
	#ifdef DEBUG
		Printf("LW, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.immediate], memoryLoaded);
	#endif
}

// I Type Instructions
void lbuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
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
	
	REG[decInstruction.rd] = memoryLoaded;
	
	#ifdef DEBUG
		Printf("LBU, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.immediate], memoryLoaded);
	#endif
}

void lhuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
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
	
	REG[decInstruction.rd] = memoryLoaded;
	
	#ifdef DEBUG
		Printf("LHU, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.immediate], memoryLoaded);
	#endif
}

void addiInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
	int32_t extendedImmediate = REG[decInstruction.immediate];
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	// Overflow ignored, rd = rs1 + rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] + REG[decInstruction.immediate];
	#ifdef DEBUG
		Printf("Addi Instruction, rd = rs1 + signExtended(imm) = %d + signExtended(%d) = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.immediate], REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] + extendedImmediate);
	#endif
}

void slliInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (REG[decInstruction.rd] == 0)
	{
		return;
	}
	
	//shamt is unsigned 5 bit value
	int32_t shamt = REG[decInstruction.immediate] & 0x1F;
	
	// Overflow ignored, rd = rs1 + rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] << shamt;
	#ifdef DEBUG
		Printf("Slli Instruction, rd = rs1 << (imm & 0x1F) = %d << %d = = %d\n", REG[decInstruction.rs1], shamt, REG[decInstruction.rs1] << shamt);
	#endif
}



// END I Type Instructions
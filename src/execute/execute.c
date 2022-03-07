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

void executeInstruction(instruction_t decInstruction)
{
	#ifdef DEBUG
	extern int32_t *REG;
	int memoryToLoad = 0; 
	#endif
	
	switch(decInstruction.instruction)
	{
		case ERROR:
			Fprintf(stderr, "Error: Executing Instruction with ERROR type instruction.\n");
			break;
		case LUI:
			luiInstruction(decInstruction);
			break;
		case AUIPC:
			auipcInstruction(decInstruction);
			break;
		case JAL:
			jalInstruction(decInstruction);
			break;
		case JALR:
			jalrInstruction(decInstruction);
			break;
		case BEQ:
			beqInstruction(decInstruction);
			break;
		case BNE:
			bneInstruction(decInstruction);
			break;
		case BLT:
			bltInstruction(decInstruction);
			break;
		case BGE:
			bgeInstruction(decInstruction);
			break;
		case BLTU:
			bltuInstruction(decInstruction);
			break;
		case BGEU:
			bgeuInstruction(decInstruction);
			break;
		/*case LB:
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
		*/	
		
		case LB: 
		case LH: 
		case LW: 
		case LBU: 
		case LHU:  
			registers_write(decInstruction.rd, loadMemory(decInstruction)); 
			#ifdef DEBUG
			memoryToLoad = loadMemory(decInstruction);
			Printf("Load = %s, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm mod 4 = %d) = %d", instructionEnumToStr(decInstruction.instruction), REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, decInstruction.immediate % 4, memoryToLoad);
			#endif
			break; 	
		
		/*case SB:
			sbInstruction(decInstruction);
			break;
		case SH:
			shInstruction(decInstruction);
			break;
		case SW:
			swInstruction(decInstruction);
			break;
		*/
		case SB: 
		case SH: 
		case SW: 
			#ifdef DEBUG
			Printf("Before: Memory[%d] = 0x%08x\n", (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), readMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4))); 
			Printf("Before: Memory[%d] = 0x%08x\n", ((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)+1), readMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)+1)); 
			#endif	
			storeMemory(decInstruction); 
			#ifdef DEBUG
			Printf("Store = %s, rs1(base) = %d, rs2 (value to store) = 0x%x, imm = %d\n", instructionEnumToStr(decInstruction.instruction), REG[decInstruction.rs1], REG[decInstruction.rs2], decInstruction.immediate);
			Printf("After: Memory[%d] = 0x%08x\n", (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4), readMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4))); 
			Printf("After: Memory[%d] = 0x%08x\n", ((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)+1), readMemory((REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4)+1)); 
			#endif	
			break; 
		case ADDI:
			addiInstruction(decInstruction);
			break;
		case SLTI:
			sltiInstruction(decInstruction);
			break;
		case SLTIU:
			sltiuInstruction(decInstruction);
			break;
		case XORI:
			xoriInstruction(decInstruction);
			break;
		case ORI:
			oriInstruction(decInstruction);
			break;
		case ANDI:
			andiInstruction(decInstruction);
			break;
		case SLLI:
			slliInstruction(decInstruction);
			break;
		case SRLI:
			srliInstruction(decInstruction);
			break;
		case SRAI:
			sraiInstruction(decInstruction);
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
			Printf("ECALL instruction execution function not implemented yet\n");
			break;
		case EBREAK:
			Printf("EBREAK instruction execution function not implemented yet\n");
			break;
		default:
			Fprintf(stderr, "Error: Executing Instruction with no valid type instruction.\n");
			break;
	}
}

#include "execute_BJ.c"
#include "execute_I.c"
#include "execute_R.c"
#include "execute_SU.c"

/*
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

// I Type Instructions
void lbInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
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
		Printf("LB, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lhInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
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
		Printf("LH, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lwInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
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
		Printf("LW, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lbuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
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
		Printf("LBU, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void lhuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
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
		Printf("LHU, rd = %d, rs1 = %d, imm = %d, rd = byte(mem[rs1/4+imm/4], imm%4) = %d", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate, memoryLoaded);
	#endif
}

void addiInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	// Overflow ignored, rd = rs1 + rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] + extendedImmediate;
	#ifdef DEBUG
		Printf("Addi Instruction, rd = rs1 + signExtended(imm) = %d + signExtended(%d) = %d + %d = %d\n", REG[decInstruction.rs1], decInstruction.immediate, REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] + extendedImmediate);
	#endif
}

void slliInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	//shamt is unsigned 5 bit value
	int32_t shamt = decInstruction.immediate & 0x1F;
	
	// Overflow ignored, rd = rs1 + rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] << shamt;
	#ifdef DEBUG
		Printf("Slli Instruction, rd = rs1 << (imm & 0x1F) = %d << %d = = %d\n", REG[decInstruction.rs1], shamt, REG[decInstruction.rs1] << shamt);
	#endif
}

void sltiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}

	//SLTI instruction	
	if (REG[decInstruction.rs1] < extendedImmediate)
	 	REG[decInstruction.rd] = 1; 
	else
	 	REG[decInstruction.rd] = 0; 
	
	#ifdef DEBUG
		Printf("SLTI, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], extendedImmediate);
	#endif
}

void sltiuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	//SLTIU instruction. NOTE TEST SLTIU rd, x0, imm sets rd to 1 if rs1 is equal to 0 and imm is equal to 1
	if ((REG[decInstruction.rs1] == 0) && (decInstruction.immediate == 1))
	{
		REG[decInstruction.rd] = 1;
	}
	else
	{
		if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t) extendedImmediate))
			REG[decInstruction.rd] = 1;
		else
			REG[decInstruction.rd] = 0;
	}
	
	#ifdef DEBUG
		Printf("SLTIU, rd = %d, rs1 = %d, (unsigned) signExtended(imm) = %u\n", REG[decInstruction.rd], REG[decInstruction.rs1], (uint32_t) extendedImmediate);
	#endif
}

void xoriInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	//rd = rs1 ^ signExtend(imm);
	REG[decInstruction.rd] = REG[decInstruction.rs1] ^ extendedImmediate;
	#ifdef DEBUG
		Printf("Xori Instruction, rd = rs1 ^ signExtended(imm) = %d ^ %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] ^ extendedImmediate);
	#endif
}

void oriInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	// rd = rs1 | rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] | extendedImmediate;
	#ifdef DEBUG
		Printf("Ori Instruction, rd = rs1 | signExtended(imm) = %d | %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] | extendedImmediate);
	#endif
}

void andiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t extendedImmediate = decInstruction.immediate;
	// Sign extend
	int32_t msb = extendedImmediate &0x00000800;
	if (msb > 0)
	{
		extendedImmediate = extendedImmediate | 0xFFFFF000;
	}
	
	//rd = rs1 & rs2;
	REG[decInstruction.rd] = REG[decInstruction.rs1] & extendedImmediate;
	#ifdef DEBUG
		Printf("Andi Instruction, rd = rs1 & signExtended(imm) = %d & %d = %d\n", REG[decInstruction.rs1], extendedImmediate, REG[decInstruction.rs1] & extendedImmediate);
	#endif
}

void srliInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	REG[decInstruction.rd] = REG[decInstruction.rs1] >> (decInstruction.immediate & 0x1F);
	
	#ifdef DEBUG
		Printf("SRLI, rd = %d, rs1 = %d, imm & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], decInstruction.immediate & 0x1F);
	#endif
}

//todo look into more
void sraiInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	int32_t msb = REG[decInstruction.rs1] & 0x80000000; // filter out all but msb
	uint32_t shamt = decInstruction.immediate & 0x1F;
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
		REG[decInstruction.rd] = REG[decInstruction.rs1] >> (decInstruction.immediate & 0x1F);
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
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	REG[decInstruction.rd] = PC + decInstruction.immediate;
	#ifdef DEBUG
		Printf("auipc Instruction, rd = pc + immediate = %d + %d = %d\n", PC, decInstruction.immediate, PC + decInstruction.immediate);
	#endif
}

void luiInstruction(instruction_t decInstruction)
{	
	extern int32_t *REG;
	
	// If rd = reg[0], return, don't do anything
	if (decInstruction.rd == 0)
	{
		Fprintf(stderr, "decInstruction.rd == 0\n");
		return;
	}
	
	REG[decInstruction.rd] = decInstruction.immediate;
	#ifdef DEBUG
		Printf("lui Instruction, rd = immediate = %d\n", decInstruction.immediate);
	#endif
}
// END U Type Instructions

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
*/
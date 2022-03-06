/**
 * @file  memory.c
 * @brief Memory commands source code
 *
 * @detail 	This memory command wrapper functions is used to operate on memory
 * 		for RISCV simulation. It accepts input in the form
 *		ECE 486/586 Final Project, Dr. Mark Faust
 *		Portland State University, Winter 2022
 *
 * @date	TBA
 *
 * @author	Stephen Short 	(steshort@pdx.edu)
 * @author	Drew Seidel	(dseidel@pdx.edu)
 * @author	Michael Weston 	(miweston@pdx.edu)
 * @author	Braden Harwood 	(bharwood@pdx.edu)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "memory.h"
#include "../wrappers/wrappers.h"
#include "../execute/execute.h"
#include "../decode/decode.h"

int32_t readMemory(int32_t memoryLocation)
{
	extern int32_t *memory;

	// Check for out of scope memory location
	if (memoryLocation < 0)
	{
		Fprintf(stderr, "Error: readMemory seeking negative memory location: %d\n", memoryLocation);
		exit(1);
	}
	if (memoryLocation > MAX_ARRAY)
	{
		Fprintf(stderr, "Error: readMemory seeking memory above maximum location: %d.\n", memoryLocation);
		exit(1);
	}

	// Return 32 bit value from memory location
	return memory[memoryLocation];
}

// TO DO - finish, not implemented yet.
int32_t loadMemory(instruction_t decInstruction)
{
	extern int32_t *memory;
	extern int32_t *REG;

	int32_t memoryLocation = (REG[decInstruction.rs1] / 4) + (decInstruction.immediate / 4);


	// Check for out of scope memory location
	if (memoryLocation < 0)
	{
		Fprintf(stderr, "Error: readMemory seeking negative memory location: %d\n", memoryLocation);
		exit(1);
	}
	if (memoryLocation > MAX_ARRAY)
	{
		Fprintf(stderr, "Error: readMemory seeking memory above maximum location: %d\n", memoryLocation);
		exit(1);
	}

	// Return 32 bit value from memory location
	int32_t memoryLoaded = memory[memoryLocation];
	int32_t nextMemoryLoaded = memory[memoryLocation+1]; 

	// size correct byte select correct
	// unsigned correct
	int32_t finalMemory = memory_alignment_filter(decInstruction, memoryLoaded, nextMemoryLoaded);

	// return word
	return finalMemory;
}

void writeMemory(int32_t memoryLocation, int32_t valueToWrite)
{
	extern int32_t *memory;

	// Check for out of scope memory location
	if (memoryLocation < 0)
	{
		Fprintf(stderr, "Error: readMemory seeking negative memory location\n");
		exit(1);
	}
	if (memoryLocation > MAX_ARRAY)
	{
		Fprintf(stderr, "Error: readMemory seeking memory above maximum location.\n");
		exit(1);
	}

	// Write 32 bit value to memory location
	memory[memoryLocation] = valueToWrite;
}


int32_t memory_alignment_filter(instruction_t decInstruction, int32_t memoryLoaded, int32_t nextMemoryLoaded)
{

	int32_t dataSize = 0x00000000; 
	bool unsigned_fetch = false; 
	int32_t alignedMemory = 0x00000000; 
	int32_t byteSelected = decInstruction.immediate % 4;

	switch (decInstruction.instruction)
	{
	case LB:
		dataSize = 0x000000FF; 
		unsigned_fetch = false; 
		alignedMemory = align(dataSize, unsigned_fetch, memoryLoaded, nextMemoryLoaded, byteSelected); 
		break;
	case LH:
		dataSize = 0x0000FFFF; 
		unsigned_fetch = false; 
		alignedMemory = align(dataSize, unsigned_fetch, memoryLoaded, nextMemoryLoaded, byteSelected); 
		break;
	case LW:
		dataSize = 0xFFFFFFFF; 
		unsigned_fetch = true; 
		alignedMemory = align(dataSize, unsigned_fetch, memoryLoaded, nextMemoryLoaded, byteSelected); 
		break;
	case LBU:
		dataSize = 0x000000FF; 
		unsigned_fetch = true; 
		alignedMemory = align(dataSize, unsigned_fetch, memoryLoaded, nextMemoryLoaded, byteSelected); 
		break;
	case LHU:
		dataSize = 0x0000FFFF; 
		unsigned_fetch = true; 
		alignedMemory = align(dataSize, unsigned_fetch, memoryLoaded, nextMemoryLoaded, byteSelected); 
	default:
		Fprintf(stderr, "Error: Executing Instruction with no valid type instruction.\n");
		break;
	}

	return alignedMemory; 
}

int32_t align(int32_t datasize, bool unsigned_fetch, int32_t memoryLoaded, int32_t nextMemoryLoaded, int32_t byteSelected)
{
	int32_t temp_alignedMemory; 
	switch(byteSelected)
	{
		case 0:
			temp_alignedMemory = (memoryLoaded & datasize);
			break;
		case 1:
			temp_alignedMemory = (memoryLoaded & (datasize >> 8)) >>  8;
			break;
		case 2:
			temp_alignedMemory = (memoryLoaded & (datasize >> 16)) >> 16;
			break;
		case 3: // Happens on a boundary, need to grab the other 8 bits
			temp_alignedMemory = ((memoryLoaded & (datasize << 24)) >> 24) | ((nextMemoryLoaded & (datasize >> 8)) << 8);
			break;
		default:
			Fprintf(stderr, "Byte select error\n");
			exit(1);
	}
	

   if(unsigned_fetch)
   {
	   return temp_alignedMemory; 
   }
   else
   {
	   int32_t msb = 0; 
	   if (datasize == 0x000000FF)
	   {
		   msb = 0x00000080; 
	   }
	   else if (datasize == 0x0000FFFF)
	   {
		   msb = 0x00000080; 
	   }
	   else
	   {
		   Printf("Error with datasize and msb. Datasize = %x", datasize); 
	   }

	   int32_t sign_extend = temp_alignedMemory & msb; 
	   if (sign_extend > 0)
	   {
		   temp_alignedMemory = temp_alignedMemory & ~datasize; 
	   }	

	   return datasize; 

   }

}
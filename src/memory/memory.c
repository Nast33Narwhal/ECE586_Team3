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

typedef struct {
	int32_t data;
	bool	watchpoint;
	bool	breakpoint;
} memWord_t;

typedef struct {
	memWord_t *address;
	unsigned   size;
} memory_t;

static memory_t memory;

void mem_init(unsigned maxSize, bool usrCmds)
{
	memory.address = Malloc(maxSize * sizeof(memWord_t));
	memory.size = maxSize;
	if (!usrCmds)
		return;

	for (unsigned i = 0; i < maxSize; i++)
	{
		memory.address[i].watchpoint = false;
		memory.address[i].breakpoint = false;
	}
}

void mem_deinit()
{
	free(memory.address);
}

int32_t readMemory(unsigned memoryLocation)
{
	// Check for out of scope memory location
	if (memoryLocation > memory.size)
	{
		Fprintf(stderr, "Error: readMemory seeking memory above maximum location: %d.\n", memoryLocation);
		exit(1);
	}

	// Return 32 bit value from memory location
	return memory.address[memoryLocation].data;
}

void writeMemory(unsigned memoryLocation, int32_t valueToWrite)
{
	// Check for out of scope memory location
	if (memoryLocation > memory.size)
	{
		Fprintf(stderr, "Error in writeMemory(): Seeking memory above maximum location(0x%08X).\n", memoryLocation*4);
		exit(1);
	}

	// Write 32 bit value to memory location
	memory.address[memoryLocation].data = valueToWrite;
}

void writeMemoryMasked(unsigned memoryLocation, int32_t valueToWrite, uint32_t mask)
{
	// Check for out of scope memory location
	if (memoryLocation > memory.size)
	{
		Fprintf(stderr, "Error in writeMemoryMasked(): Seeking memory above maximum location(0x%08X).\n", memoryLocation*4);
		exit(1);
	}

	int32_t oldData = memory.address[memoryLocation].data;
	memory.address[memoryLocation].data = (valueToWrite & mask) | (oldData & ~mask);
}

void printMemory()
{
	uint32_t state = 0;
	for(unsigned i = 0; i < memory.size; i++)
	{
		if (memory.address[i].data != 0)
		{
			Printf("memory[0x%08X] = 0x%08x\n", i*4, memory.address[i].data);
			state = 0;
		}
		else if ((memory.address[i].data == 0) && (state == 0))
		{
			Printf("memory[0x%08X] = 0x%08x\n", i*4, memory.address[i].data);
			state = 1;
		}
		else if ((memory.address[i].data == 0) && (state == 1))
		{
			Printf("...\n");
			state = 2;
		}
		else
		{
			// Do nothing unless we are at the end of the memory and last thing printed was ...
			if(i == (memory.size-1))
			{
				Printf("memory[0x%08X] = 0x%08x\n", i*4, memory.address[i].data);
			}
		}
	}
}
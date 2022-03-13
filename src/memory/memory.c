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

#define RED   "\x1B[31m"
#define DEFAULT "\x1B[0m"

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

void mem_init(unsigned maxSize)
{
	memory.address = Malloc(maxSize * sizeof(memWord_t));
	memory.size = maxSize;

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

void setBreakpoint(unsigned location)
{
	if (location > memory.size)
	{
		Fprintf(stderr, "Warning in setBreakpoint(): Seeking memory above maximum location(0x%08X).\n", location*4);
		return;		
	}

	memory.address[location].breakpoint = true;
}

void clrBreakpoint(unsigned location)
{
	if (location > memory.size)
	{
		Fprintf(stderr, "Warning in clrBreakpoint(): Seeking memory above maximum location(0x%08X).\n", location*4);
		return;		
	}

	memory.address[location].breakpoint = true;
}

bool isBreakpoint(unsigned location)
{
	if (location > memory.size)
	{
		Fprintf(stderr, "Warning in isBreakpoint(): Seeking memory above maximum location(0x%08X).\n", location*4);
		return false;		
	}

	return memory.address[location].breakpoint;
}

void setWatchpoint(unsigned location)
{
	if (location > memory.size)
	{
		Fprintf(stderr, "Warning in setWatchpoint(): Seeking memory above maximum location(0x%08X).\n", location*4);
		return;		
	}

	memory.address[location].watchpoint = true;
}

void clrWatchpoint(unsigned location)
{
	if (location > memory.size)
	{
		Fprintf(stderr, "Warning in clrWatchpoint(): Seeking memory above maximum location(0x%08X).\n", location*4);
		return;		
	}

	memory.address[location].watchpoint = true;
}

bool isWatchpoint(unsigned location)
{
	if (location > memory.size)
	{
		Fprintf(stderr, "Warning in isWatchpoint(): Seeking memory above maximum location(0x%08X).\n", location*4);
		return false;		
	}

	return memory.address[location].watchpoint;
}

unsigned mem_getSize()
{
	return memory.size;
}

void printMemory(uint32_t address, int8_t offset)
{
	char color[10]; 
	uint32_t state = 0;
	bool state_exception = false; //still print zeros if they were just written to the memory location

	for(unsigned i = 0; i < memory.size; i++)
	{
		if (i == address){
			strcpy(color, RED); 
			state_exception = true; 
		}
		else if (i == address + 1 && offset > 0)
		{
			strcpy(color, RED); 
			state_exception = true; 
		}
		else
		{
			strcpy(color, DEFAULT); 
			state_exception = false; 
		}

		if (memory.address[i].data != 0)
		{
			Printf("%smemory[0x%08X] = 0x%08x\n" DEFAULT, color, i*4, memory.address[i].data);
			state = 0;
		}
		else if (((memory.address[i].data == 0) && (state == 0)) || ((memory.address[i].data == 0) && (state_exception == true)))
		{
			Printf("%smemory[0x%08X] = 0x%08x\n" DEFAULT, color,  i*4, memory.address[i].data);
			state = 1;
		}
		else if ((memory.address[i].data == 0) && (state == 1) && (state_exception == false))
		{
			Printf("...\n");
			state = 2;
		}
		else
		{
			// Do nothing unless we are at the end of the memory and last thing printed was ...
			if(i == (memory.size-1))
			{
				Printf("%smemory[0x%08X] = 0x%08x\n" DEFAULT, color, i*4, memory.address[i].data);
			}
		}
	}
}
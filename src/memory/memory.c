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

int32_t readMemory(int32_t memoryLocation)
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
	
	// Return 32 bit value from memory location
	return memory[memoryLocation];
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

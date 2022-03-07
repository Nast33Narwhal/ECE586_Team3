/**
 * @file memory.h
 * @brief Memory Commands header file
 *
 * @detail 	This header file contains all of the constants, enums, structs, and function prototypes
 *		used for the memory read and write commands.
 *		ECE 486/586 Final Project, Dr. Mark Faust
 *		Portland State University,  Winter 2022
 *
 * @date	Presented March, 2022
 *
 * @author	Stephen Short	(steshort@pdx.edu)
 * @author	Drew Seidel	(dseidel@pdx.edu)
 * @author	Michael Weston 	(miweston@pdx.edu)
 * @author	Braden Harwood 	(bharwood@pdx.edu)
 * 		
 */
#ifndef _MEMORY_H
#define _MEMORY_H


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "../decode/decode.h"
#include "../wrappers/wrappers.h"
#include "../execute/execute.h"


#define MAX_ARRAY 16384

int32_t readMemory(int32_t memoryLocation);

//to do write function header 
int32_t loadMemory(instruction_t decInstruction); 

void writeMemory(int32_t memoryLocation, int32_t valueToWrite);

//todo write function header
int32_t load_memory_alignment_filter(instruction_t decInstruction, int32_t memoryLoaded, int32_t nextMemoryLoaded); 

//to do write function header 
int32_t load_align(int32_t datasize, bool unsigned_fetch, int32_t memoryLoaded, int32_t nextMemoryLoaded, int32_t byteSelected); 


//to do write function header 
void storeMemory(instruction_t decInstruction); 

//to do write function header
void store_memory_alignment_filter(instruction_t decInstruction, int32_t *finalValueToStore, int32_t *next_finalValueToStore, int32_t valueToStore); 


#endif

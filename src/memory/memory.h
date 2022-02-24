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

#define MAX_ARRAY 16384

int32_t readMemory(int32_t memoryLocation);

void writeMemory(int32_t memoryLocation, int32_t valueToWrite);
#endif

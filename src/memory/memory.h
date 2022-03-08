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

/**
 * @fn      mem_init()
 * @brief   Initializes the system memory for the simulator
 * 
 * @param   maxSize Maximum number of 32 bit words the memory can contain
 * @param   usrCmds If true, also initializes breakpoints and watchpoints for
 *                  memory locations
 */
void mem_init(unsigned maxSize, bool usrCmds);

/**
 * @fn      mem_deinit()
 * @brief   Frees allocated memory
 */
void mem_deinit(void);

int32_t readMemory(unsigned memoryLocation);

void writeMemory(unsigned memoryLocation, int32_t valueToWrite);

/**
 * @fn      writeMemoryMasked
 * @brief   Overwrites the masked bits at an address with the provided bits
 * 
 * @param memoryLocation Word address to write to
 * @param valueToWrite   Value to be masked and then written
 * @param mask           Mask denoting bits in memory word that will be overwritten
 */
void writeMemoryMasked(unsigned memoryLocation, int32_t valueToWrite, uint32_t mask);

/**
 * @fn      printMemory
 * @brief   Prints entire memory contents to stdout
 */
void printMemory(void);

#endif

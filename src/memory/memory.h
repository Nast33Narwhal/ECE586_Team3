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
 */
void mem_init(unsigned maxSize);

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
 * @fn      setBreakpoint
 * @brief   Sets a breakpoint at the specified word
 * 
 * @param   location    Word aligned address of the breakpoint
 */
void setBreakpoint(unsigned location);

/**
 * @fn      clrBreakpoint
 * @brief   Clears a breakpoint at the specified word
 * 
 * @param   location    Word aligned address of the breakpoint
 */
void clrBreakpoint(unsigned location);

/**
 * @fn      isBreakpoint
 * @brief   Check if memory word is a breakpoint
 * 
 * @param   location Address of memory word
 * @return  true if the memory word is a breakpoint, false otherwise 
 */
bool isBreakpoint(unsigned location);

/**
 * @fn      setWatchpoint
 * @brief   Sets a watchpoint at the specified word
 * 
 * @param   location    Word aligned address of the watchpoint
 */
void setWatchpoint(unsigned location);

/**
 * @fn      clrWatchpoint
 * @brief   Clears a watchpoint at the specified word
 * 
 * @param   location    Word aligned address of the watchpoint
 */
void clrWatchpoint(unsigned location);

/**
 * @fn      isWatchpoint
 * @brief   Check if memory word is a watchpoint
 * 
 * @param   location Address of memory word
 * @return  true if the memory word is a watchpoint, false otherwise 
 */
bool isWatchpoint(unsigned location);

/**
 * @fn      mem_getSize
 * @brief   Returns the number of memWords_t in memory
 * 
 * @return  Number of memWords_t in memory
 */
unsigned mem_getSize(void);

/**
 * @fn      printMemory
 * @brief   Prints entire memory contents to stdout
 *          address and offset not needed. Specify printMemory(-1,-1) if just printing contents
 *          Give address if you are printing memory in such a state where you want to denote 
 *          in red a memory address that what just written to like so: printMemory(address, offset)
 */
void printMemory(uint32_t address, int8_t offset);

#endif

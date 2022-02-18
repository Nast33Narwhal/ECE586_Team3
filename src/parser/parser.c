/**
 * @file  parser.c
 * @brief File input parser source code for DRAM memory controller simulation
 *
 * @detail 	This parser is used to parse through memory image files
 * 		for RISCV simulation. It accepts input in the form
 *		<adress location> <memory contents in hex> 
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
#include "parser.h"
#include "../wrappers/wrappers.h"

#define max_array 16384

int memory_size; 

int* parser(char *fileName){ 

	FILE *fp; 
	fp = Fopen(fileName, "r"); 
	char *line = Malloc(128 * sizeof(char)); 


	int i = 0; 
	unsigned int address ; 
	unsigned int address_contents; 
    int *memory = Malloc(sizeof(int) * max_array); //initially allocate 64KiB

	
	while ((fgets(line, 128, fp) != NULL))
	{
		sscanf(line, " %u: %x", &address, &address_contents); 
		memory[i] = address_contents; 
		i++; 
		if (i > max_array)
		{
			Printf("Error. Memory file bigger than 64KB\n"); 
			exit(-1);
		}
	}
		memory_size = i; 
        memory = realloc(memory, sizeof(int) * memory_size); //resize to size of actual memory

	
	

    return memory; 
}
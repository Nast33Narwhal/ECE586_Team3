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
#include "../memory/memory.h"

#define MAX_LINE_SIZE 128

int32_t memory_size;  

void parseMemFile(char *fileName){ 

	FILE *fp; 
	fp = Fopen(fileName, "r"); 
	char *line = Malloc(MAX_LINE_SIZE * sizeof(char)); 
	#ifdef DEBUG
		FILE *outFile = Fopen("outfile.mem", "w+"); // Create output file and empty it.
	#endif


	int32_t i = 0; 
	uint32_t address; 
	uint32_t address_contents; 

	
	while ((fgets(line, MAX_LINE_SIZE, fp) != NULL))
	{
		sscanf(line, " %x: %x\n", &address, &address_contents);
		writeMemory((unsigned)(address/4), (int32_t)address_contents);
		
		#ifdef DEBUG
			Fprintf(outFile, "%4x:    %08x\n", address, address_contents);
		#endif
		
		i++; 
	}
	
	memory_size = i; 
        //memory = realloc(memory, sizeof(int) * memory_size); //resize to size of actual memory // We shouldn't resize as stack goes to the top

	// Close file
	Fclose(fp);
	#ifdef DEBUG
		Fclose(outFile);
	#endif
}

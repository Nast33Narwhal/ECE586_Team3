#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "./parser/parser.h"
#include "./wrappers/wrappers.h"
#include "./registers/registers.h"
#include "./decode/decode.h"
#include "./memory/memory.h"
#include "./execute/execute.h"
#include "./userInterface/userInterface.h"

#define MEM_SIZE 16384

//Helper functions
char *parseArgs(int32_t argc, char **argv);
void writeToWatchpoint(unsigned address);

// global variables
uint32_t stackAddress = 0; //fix (unneccesary global)
extern int32_t memory_size; 	//how many values in dynamically allocated memory array. fix
uint32_t PC = 0; 
//registers_t *registers; 
int32_t *REG;  //global array of registers
bool singleStep = false;

int32_t main(int32_t argc, char **argv)
{
	//parse args
	char *fileName = parseArgs(argc, argv);
	
	mem_init(MEM_SIZE);

	//load program 
   	parseMemFile(fileName); 

	//set initial values
	REG = registers_init();

	#ifdef DEBUG
		Printf("\n\nDEBUG INITIAL STATES\n");
		Printf("Filename: %s \nStarting Adress: %d \nStack Address: %d\n\n", fileName, PC, stackAddress);

		printRegisters(); 
		printMemory(-1,-1);		//-1 to denote no store operation for alterations in memory. no byte offset applicable
	#endif
	


	//initialize decodedInstruction type
	instruction_t decInstruction;
	int32_t nextInstruction;

	//main loop
    
	while(1)
	{
		nextInstruction = readMemory(PC/4);//get instruction from memory[PC/4]
		#ifdef DEBUG	
			Printf("\nPC = %d = 0x%.8x\n", PC, PC);
		#endif
		
		decodeInstruction(nextInstruction, &decInstruction);
		#ifdef DEBUG
			//Printf("nextInstruction = 0x%08X\n", nextInstruction);
			printInstruction(&decInstruction);
		#endif

		if (isBreakpoint(PC/4)) //Check if we're at a breakpoint
		{
			Fprintf(stdout, "Breakpoint at 0x%08X\n", PC);
			displayUserInterface(&singleStep);
		}
		else if (singleStep) //Check if we just stepped through a command
		{
			displayUserInterface(&singleStep);
		}
		
		// Decoded end program condition
		if ((nextInstruction == 0x8067) && (REG[1] == 0))
		{	
			#if defined(DEBUG) || defined(VERBOSE)
			Printf("JR RA, where value in RA = 0, meaning end program should be triggered.\n");
			#endif
			break;
		}
		
	

		//execute instruction
		executeInstruction(decInstruction);


		#ifdef VERBOSE
		Printf("Instruction Completed:\n"); 
		printInstructionSimple(&decInstruction); 
		printRegisters(); 
		#endif

		#ifdef REG_MEM
		Printf("\nRegister States After Completion:\n"); 
		if (decInstruction.instruction == ECALL)
		{
		printRegisters_Debug(10);  //color a0 if the instruction was ecall
		}
		else
		{
		printRegisters_Debug(decInstruction.rd); 
		}
		Printf("\nMemory States After Completion:\n"); 
		uint32_t address = (unsigned)(REG[decInstruction.rs1] + signExtend(decInstruction.immediate,11));
		uint8_t offset = address % 4;  
		if(decInstruction.instruction == SB)
		{
			printMemory(address/4, -1); 					     //no offset needed for bytes
		}
		else if (decInstruction.instruction == SH)				
		{
			printMemory(address/4, (offset > 2) ? offset : - 1); 	//only give offset if greater than 2 for half word
		}
		else if (decInstruction.instruction == SW)
		{
			printMemory(address/4, offset); 					//if greater than zero next word will also be red
		}
		else if (decInstruction.instruction == ECALL)
		{
			address = REG[11]; 
			offset  = REG[12]/4; 
			printMemory(address/4, (offset > 4) ? offset: -1); 	
		}
		else
		{ 
		printMemory(-1,-1); //-1 to denote no store operation for alterations in memory. no byte offset applicable
		} 
		Printf("\n\n\n\n"); 
		#endif
		
		PC += 4; // Should update PC when executing the instruction.
	}
	

	#ifdef DEBUG
	Printf("\n\nDEBUG RESULTS\n");
	Printf("PC=%d, SP=%d, RA=%d\n\n", PC, REG[2], REG[1]);
	#endif

	//print registers
	printRegisters(); 

	

	#ifdef DEBUG
	printMemory(-1, -1); //-1 to denote no store operation for alterations in memory. no byte offset applicable
	#endif

	//free(registers)
	mem_deinit();
	free(REG);
    return 0;
}

/**
 * @fn      writeToWatchpoint
 * @brief   Prompts the user that a watchpoint is about to be overwritten
 * 
 * @param   address Address of the watchpoint in memory
 */
void writeToWatchpoint(unsigned address)
{
    Printf("Attempting to write to watchpoint at 0x%08X\n", address);
    displayUserInterface(&singleStep);
}

char *parseArgs(int32_t argc, char **argv)
{

    char *fileName = NULL;
    // adding in case he wants an outfile later on.
    //char *outFile = NULL;
   // bool out_flag = false;
    stackAddress = 65536;
    int32_t initAddress = 0;

    for (int32_t i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            if (fileName == NULL)
            {
                fileName = argv[i];
            }
            else
            {
            Printf("Error in main.c: Multiple input file names provided:\n%s\n%s\n", fileName, argv[i]);
            return NULL;
            }
        }

       
        else if (!strcmp(argv[i], "-sp")) 
		{
			if (i+1 == argc)
				Fprintf(stderr, "No parameter after -sp flag\n");
			else if (!isNumber(argv[i+1]))
				Fprintf(stderr, "Invalid argument %s after -sp. Expected number\n", argv[i+1]);
			else
			{
				i++;
				uint64_t convert = atol(argv[i]);
				if (convert < 0 || convert > UINT32_MAX)
				{
					Fprintf(stderr, "Invalid argument for -sp. Must be between 0 and %u. Defaulting to 65536\n", UINT32_MAX);
				}
				else
					stackAddress = (unsigned int)convert;	
			}
		}

		else if (!strcmp(argv[i], "-ui")) 
		{
			singleStep = true;
		}

        else if (!strcmp(argv[i], "-pc")) 
		{
			if (i+1 == argc)
				Fprintf(stderr, "No parameter after -pc  flag\n");
			else if (!isNumber(argv[i+1]))
				Fprintf(stderr, "Invalid argument %s after -pc. Expected number\n", argv[i+1]);
			else
			{
				i++;
				uint64_t convert = atol(argv[i]);
				if (convert < 0 || convert > UINT32_MAX)
					Fprintf(stderr, "Invalid argument for -pc. Must be between 0 and %u. Defaulting to 0\n", UINT32_MAX);
				else if (convert % 4 != 0)
					Fprintf(stderr, "Invalid argument for -pc. Must be a multiple of 4. Defaulting to 0\n");
				else
				{
					initAddress = (unsigned int)convert;	
					PC = initAddress; 
				}
			}
		}
        
        
    }

    if(fileName == NULL)
		fileName = "program.mem"; 
	

    return fileName;
}







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

#define MAX_ARRAY 16384

// global variables
uint32_t stackAddress = 0; //fix (unneccesary global)
int32_t *memory; 				//dynamically allocated memory space
extern int32_t memory_size; 	//how many values in dynamically allocated memory array. fix
uint32_t PC = 0; 
//registers_t *registers; 
int32_t *REG;  //global array of registers

char *parseArgs(int32_t argc, char **argv);
void printRegisters(); 
void printMemory();


int32_t main(int32_t argc, char **argv)
{
	//parse args
	char *fileName = parseArgs(argc, argv);
	
	//load program 
   	memory = parseMemFile(fileName); 
	#ifdef DEBUG
		printMemory();
	#endif
	
	//set initial values
	REG = registers_init();

	//initialize decodedInstruction type
	instruction_t decInstruction;
	int32_t nextInstruction;

	//main loop
    
	while(1)
	{
		nextInstruction = readMemory(PC/4);//get instruction from memory[PC/4]
		#ifdef DEBUG	
			Printf("PC = %d = 0x%.8x\n", PC, PC);
			Printf("nextInstruction = 0x%08X\n", nextInstruction);
		#endif
		
		decodeInstruction(nextInstruction, &decInstruction);
		#ifdef DEBUG
			printInstruction(nextInstruction, &decInstruction);
		#endif
		if ((nextInstruction == 0x8067) && (REG[1] == 0))
		{
			Printf("JR RA, where value in RA = 0, meaning end program should be triggered.\n");
			break;
		}
		//if PC/4 > memory_size, exit; 
		//decode instruction
		//execute instruction
		PC += 4; // Should update PC when executing the instruction.
	}

	//print registers
	printRegisters(); 

	

	#ifdef DEBUG
	//temporay checking result, parsing
	Printf("\n\nDEBUG RESULTS\n"); 
    Printf("Filename: %s \nStarting Adress: %d \nStack Address: %d\n\n", fileName, PC, stackAddress); 
	
	//temporary checking result, PC, SP, RA
	Printf("PC=%d, SP=%d, RA=%d\n\n", PC, REG[2], REG[1]); 
	
	//memory array
	Printf("Number of array elements is: %d\n", memory_size); 
	for (int32_t i = 0; i < memory_size; i++)
	{
		printf("Mem %02X :0x%08X\n", i*4, memory[i]); 
	}
	#endif

	//free(registers);
	free(memory); 
	free(REG); 
    return 0;
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




void printRegisters(){

	/*Printf(" X0: 0x%08x\n", registers->zero);
	Printf(" PC: 0x%08x\n", registers->pc);
	Printf(" RA: 0x%08x\n", registers->ra);
	Printf(" SP: 0x%08x\n", registers->sp);
	Printf(" GP: 0x%08x\n", registers->gp);
	Printf(" TP: 0x%08x\n", registers->tp);
	Printf(" T0: 0x%08x\n", registers->t0);
	Printf(" T1: 0x%08x\n", registers->t1);
	Printf(" T2: 0x%08x\n", registers->t2);
	Printf(" T3: 0x%08x\n", registers->t3);
	Printf(" T4: 0x%08x\n", registers->t4);
	Printf(" T5: 0x%08x\n", registers->t5);
	Printf(" T6: 0x%08x\n", registers->t6);
	Printf(" S0: 0x%08x\n", registers->s0);
	Printf(" S1: 0x%08x\n", registers->s1);
	Printf(" S2: 0x%08x\n", registers->s2);
	Printf(" S3: 0x%08x\n", registers->s3);
	Printf(" S4: 0x%08x\n", registers->s4);
	Printf(" S5: 0x%08x\n", registers->s5);
	Printf(" S6: 0x%08x\n", registers->s6);
	Printf(" S7: 0x%08x\n", registers->s7);
	Printf(" S8: 0x%08x\n", registers->s8);
	Printf(" S9: 0x%08x\n", registers->s9);
	Printf("S10: 0x%08x\n", registers->s10);
	Printf("S11: 0x%08x\n", registers->s11);
	Printf(" A0: 0x%08x\n", registers->a0);
	Printf(" A1: 0x%08x\n", registers->a1);
	Printf(" A2: 0x%08x\n", registers->a2);
	Printf(" A3: 0x%08x\n", registers->a3);
	Printf(" A4: 0x%08x\n", registers->a4);
	Printf(" A5: 0x%08x\n", registers->a5);
	Printf(" A6: 0x%08x\n", registers->a6);
	Printf(" A7: 0x%08x\n", registers->a7);
	*/

	Printf("  PC: 0x%08x\n", PC);
	Printf("  X0: 0x%08x\n", REG[0]);
	Printf("RAX1: 0x%08x\n", REG[1]);
	Printf("SPX2: 0x%08x\n", REG[2]);
	Printf("  X3: 0x%08x\n", REG[3]);
	Printf("  X4: 0x%08x\n", REG[4]);
	Printf("  X5: 0x%08x\n", REG[5]);
	Printf("  X6: 0x%08x\n", REG[6]);
	Printf("  X7: 0x%08x\n", REG[7]);
	Printf("  X8: 0x%08x\n", REG[8]);
	Printf("  X9: 0x%08x\n", REG[9]);
	Printf(" X10: 0x%08x\n", REG[10]);
	Printf(" X11: 0x%08x\n", REG[11]);
	Printf(" X12: 0x%08x\n", REG[12]);
	Printf(" X13: 0x%08x\n", REG[13]);
	Printf(" X14: 0x%08x\n", REG[14]);
	Printf(" X15: 0x%08x\n", REG[15]);
	Printf(" X16: 0x%08x\n", REG[16]);
	Printf(" X17: 0x%08x\n", REG[17]);
	Printf(" X18: 0x%08x\n", REG[18]);
	Printf(" X19: 0x%08x\n", REG[19]);
	Printf(" X20: 0x%08x\n", REG[20]);
	Printf(" X21: 0x%08x\n", REG[21]);
	Printf(" X22: 0x%08x\n", REG[22]);
	Printf(" X23: 0x%08x\n", REG[23]);
	Printf(" X24: 0x%08x\n", REG[24]);
	Printf(" X25: 0x%08x\n", REG[25]);
	Printf(" X26: 0x%08x\n", REG[26]);
	Printf(" X27: 0x%08x\n", REG[27]);
	Printf(" X28: 0x%08x\n", REG[28]);
	Printf(" X29: 0x%08x\n", REG[29]);
	Printf(" X30: 0x%08x\n", REG[30]);
	Printf(" X31: 0x%08x\n", REG[31]);
}

void printMemory()
{
	for(int32_t i = 0; i != memory_size; i++)
	{
		Printf("memory[%2d] = 0x%08x\n", i, memory[i]);
	}
}


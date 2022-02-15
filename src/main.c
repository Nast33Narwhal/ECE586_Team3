#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./wrappers/wrappers.h"
#include "./registers/registers.h"

#define max_array 16384


// global variables
unsigned int stackAddress = 0;
unsigned int initAddress = 0;
int memory[max_array]; 
registers_t *registers; 

char *parseArgs(int argc, char **argv);
void parser(char *fileName); 
void printRegisters(); 


int main(int argc, char **argv)
{
	//parse args
    char *fileName = parseArgs(argc, argv);
	
	//load program 
    parser(fileName); 

	//set initial values
	registers = registers_init(); 


	/*main loop

	while(!done)
		get instruction from memory[PC/4]
		decode instruction
		execute instruction

	*/

	//print registers
	printRegisters(); 

	

	#ifdef DEBUG
	//temporay checking result
    Printf("Filename: %s \nStarting Adress: %d \nStack Address: %d\n", fileName, initAddress, stackAddress); 
	#endif

	#ifdef DEBUG
	//temporary checking result
	Printf("PC = %d, SP = %d, RA = %d\n", registers->pc, registers->sp, registers->ra); 
	#endif


    return 0;
}


char *parseArgs(int argc, char **argv)
{

    char *fileName = NULL;
    // adding in case he wants an outfile later on.
    //char *outFile = NULL;
   // bool out_flag = false;
    stackAddress = 65536;
    initAddress = 0;

    for (int i = 1; i < argc; i++)
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
				long int convert = atol(argv[i]);
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
				long int convert = atol(argv[i]);
				if (convert < 0 || convert > UINT32_MAX)
					Fprintf(stderr, "Invalid argument for -pc. Must be between 0 and %u. Defaulting to 0\n", UINT32_MAX);
				else if (convert % 4 != 0)
					Fprintf(stderr, "Invalid argument for -pc. Must be a multiple of 4. Defaulting to 0\n");
				else
					initAddress = (unsigned int)convert;	
			}
		}
        
        
    }

    if(fileName == NULL)
		fileName = "program.mem"; 
	

    return fileName;
}


void parser(char *fileName){ 

	FILE *fp; 
	fp = Fopen(fileName, "r"); 
	char *line = Malloc(128 * sizeof(char)); 


	int i = 0; 
	unsigned int address ; 
	unsigned int address_contents; 
	
	while ((fgets(line, 128, fp) != NULL))
	{
		sscanf(line, " %u: %x", &address, &address_contents); 
		memory[i] = address_contents; 
		i++; 
		if (i > max_array)
			Printf("Error. Memory file bigger than 64KB\n"); 
	}

	
	#ifdef DEBUG
	int array_size = i; 
	for (i = 0; i < array_size; i++)
	{
		printf("Mem %02x :%08x\n", i*4, memory[i]); 
	}
	#endif

}

void printRegisters(){

	Printf(" X0: 0x%08x\n", registers->zero);
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

}
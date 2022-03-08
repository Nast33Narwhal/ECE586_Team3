#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "registers.h"
#include "../wrappers/wrappers.h"


//TO DO, map registers to english names in enum, etc. 

//initilize registers
int32_t* registers_init(){
    
    extern int32_t stackAddress; 
    int32_t *REG = Malloc (sizeof(int32_t) * 32);  
    REG[0] = 0x00000000;    //zero registers
    REG[1] = 0x00000000;    //Return address 
    REG[2] = stackAddress;  //SP

    #ifdef DEBUG
    for (int i = 3; i < 32; i++){
        REG[i] = 0; 
    }
    #endif

    return REG; 

}


/*
registers_t *registers_init()
{

    //he doesnt want the other registers initilaized so this is a quick fix
    registers_t *init_reg = Malloc(sizeof(registers_t)); 
    extern int32_t stackAddress; 
    extern int32_t initAddress; 

    init_reg->zero = 0x00000000; //fix to make constant
    init_reg->sp = stackAddress; 
    init_reg->pc = initAddress; 
    init_reg->ra = 0; 

    return init_reg; 
    
}
*/

void registers_write(uint8_t regNum, uint32_t data)
{
    extern int32_t *REG;
    if (regNum > 31)
    {
        Fprintf(stderr, "ERROR in registers_write: Register number %d out of bounds.\n", regNum);
        return;
    }

    if (regNum == 0)
        return;

    REG[regNum] = data;
}

void printRegisters(){
    extern int32_t *REG;
	extern uint32_t PC; 
	
	Printf("\n");
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
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
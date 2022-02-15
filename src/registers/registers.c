#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "registers.h"
#include "../wrappers/wrappers.h"



registers_t *registers_init()
{

    //he doesnt want the other registers initilaized so this is a quick fix
    registers_t temp; 
    registers_t *init_reg = &temp; //= Malloc(sizeof(registers_t)); 
    extern int stackAddress; 
    extern int initAddress; 

    init_reg->zero = 0x00000000; //fix to make constant
    init_reg->sp = stackAddress; 
    init_reg->pc = initAddress; 
    init_reg->ra = 0; 

    return init_reg; 
    
}
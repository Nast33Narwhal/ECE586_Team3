#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "registers.h"
#include "../wrappers/wrappers.h"
#define RED   "\x1B[31m"
#define DEFAULT "\x1B[0m"

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
	Printf("      pc: 0x%08x\n", PC);
	Printf(" zero/x0: 0x%08x\n", REG[0]);
	Printf("   ra/x1: 0x%08x\n", REG[1]);
	Printf("   sp/x2: 0x%08x\n", REG[2]);
	Printf("   gp/x3: 0x%08x\n", REG[3]);
	Printf("   tp/x4: 0x%08x\n", REG[4]);
	Printf("   t0/x5: 0x%08x\n", REG[5]);
	Printf("   t1/x6: 0x%08x\n", REG[6]);
	Printf("   t2/x7: 0x%08x\n", REG[7]);
	Printf("s0/fp/x8: 0x%08x\n", REG[8]);
	Printf("   s1/x9: 0x%08x\n", REG[9]);
	Printf("  a0/x10: 0x%08x\n", REG[10]);
	Printf("  a1/x11: 0x%08x\n", REG[11]);
	Printf("  a2/x12: 0x%08x\n", REG[12]);
	Printf("  a3/x13: 0x%08x\n", REG[13]);
	Printf("  a4/x14: 0x%08x\n", REG[14]);
	Printf("  a5/x15: 0x%08x\n", REG[15]);
	Printf("  a6/x16: 0x%08x\n", REG[16]);
	Printf("  a7/x17: 0x%08x\n", REG[17]);
	Printf("  s2/x18: 0x%08x\n", REG[18]);
	Printf("  s3/x19: 0x%08x\n", REG[19]);
	Printf("  s4/x20: 0x%08x\n", REG[20]);
	Printf("  s5/x21: 0x%08x\n", REG[21]);
	Printf("  s6/x22: 0x%08x\n", REG[22]);
	Printf("  s7/x23: 0x%08x\n", REG[23]);
	Printf("  s8/x24: 0x%08x\n", REG[24]);
	Printf("  s9/x25: 0x%08x\n", REG[25]);
	Printf(" s10/x26: 0x%08x\n", REG[26]);
	Printf(" s11/x27: 0x%08x\n", REG[27]);
	Printf("  t3/x28: 0x%08x\n", REG[28]);
	Printf("  t4/x29: 0x%08x\n", REG[29]);
	Printf("  t5/x30: 0x%08x\n", REG[30]);
	Printf("  t6/x31: 0x%08x\n", REG[31]);
	Printf("\n");
}

void printRegisters_Debug(uint8_t regNum)
{
    extern int32_t *REG;
	extern uint32_t PC; 
	int i; 
	char color[32][10]; 

	for (i = 0; i < 32; i++)
	{
		if(regNum == i)
			strcpy(color[i], RED); 
		else
			strcpy(color[i], DEFAULT); 
	}
	
	Printf("\n");
	Printf("      pc: 0x%08x\n", PC);
	Printf("%s zero/x0: 0x%08x\n" DEFAULT, color[0], REG[0]);
	Printf("%s   ra/x1: 0x%08x\n" DEFAULT, color[1], REG[1]);
	Printf("%s   sp/x2: 0x%08x\n" DEFAULT, color[2], REG[2]);
	Printf("%s   gp/x3: 0x%08x\n" DEFAULT, color[3], REG[3]);
	Printf("%s   tp/x4: 0x%08x\n" DEFAULT, color[4], REG[4]);
	Printf("%s   t0/x5: 0x%08x\n" DEFAULT, color[5], REG[5]);
	Printf("%s   t1/x6: 0x%08x\n" DEFAULT, color[6], REG[6]);
	Printf("%s   t2/x7: 0x%08x\n" DEFAULT, color[7], REG[7]);
	Printf("%ss0/fp/x8: 0x%08x\n" DEFAULT, color[8], REG[8]);
	Printf("%s   s1/x9: 0x%08x\n" DEFAULT, color[9],  REG[9]);
	Printf("%s  a0/x10: 0x%08x\n" DEFAULT, color[0], REG[10]);
	Printf("%s  a1/x11: 0x%08x\n" DEFAULT, color[11], REG[11]);
	Printf("%s  a2/x12: 0x%08x\n" DEFAULT, color[12], REG[12]);
	Printf("%s  a3/x13: 0x%08x\n" DEFAULT, color[13], REG[13]);
	Printf("%s  a4/x14: 0x%08x\n" DEFAULT, color[14], REG[14]);
	Printf("%s  a5/x15: 0x%08x\n" DEFAULT, color[15], REG[15]);
	Printf("%s  a6/x16: 0x%08x\n" DEFAULT, color[16], REG[16]);
	Printf("%s  a7/x17: 0x%08x\n" DEFAULT, color[17], REG[17]);
	Printf("%s  s2/x18: 0x%08x\n" DEFAULT, color[18], REG[18]);
	Printf("%s  s3/x19: 0x%08x\n" DEFAULT, color[19], REG[19]);
	Printf("%s  s4/x20: 0x%08x\n" DEFAULT, color[20], REG[20]);
	Printf("%s  s5/x21: 0x%08x\n" DEFAULT, color[21], REG[21]);
	Printf("%s  s6/x22: 0x%08x\n" DEFAULT, color[22], REG[22]);
	Printf("%s  s7/x23: 0x%08x\n" DEFAULT, color[23], REG[23]);
	Printf("%s  s8/x24: 0x%08x\n" DEFAULT, color[24], REG[24]);
	Printf("%s  s9/x25: 0x%08x\n" DEFAULT, color[25], REG[25]);
	Printf("%s s10/x26: 0x%08x\n" DEFAULT, color[26], REG[26]);
	Printf("%s s11/x27: 0x%08x\n" DEFAULT, color[27], REG[27]);
	Printf("%s  t3/x28: 0x%08x\n" DEFAULT, color[28], REG[28]);
	Printf("%s  t4/x29: 0x%08x\n" DEFAULT, color[29], REG[29]);
	Printf("%s  t5/x30: 0x%08x\n" DEFAULT, color[30], REG[30]);
	Printf("%s  t6/x31: 0x%08x\n" DEFAULT, color[31], REG[31]);
	Printf("\n");
}

const char *regNumToStr(uint8_t regNum)
{
	switch(regNum)
	{
		case (0): return "zero";
		case (1): return "ra";
		case (2): return "sp";
		case (3): return "gp";
		case (4): return "tp";
		case (5): return "t0";
		case (6): return "t1";
		case (7): return "t2";
		case (8): return "s0";
		case (9): return "s1";
		case (10): return "a0";
		case (11): return "a1";
		case (12): return "a2";
		case (13): return "a3";
		case (14): return "a4";
		case (15): return "a5";
		case (16): return "a6";
		case (17): return "a7";
		case (18): return "s2";
		case (19): return "s3";
		case (20): return "s4";
		case (21): return "s5";
		case (22): return "s6";
		case (23): return "s7";
		case (24): return "s8";
		case (25): return "s9";
		case (26): return "s10";
		case (27): return "s11";
		case (28): return "t3";
		case (29): return "t4";
		case (30): return "t5";
		case (31): return "t6";
	}
	return "ERROR";
}
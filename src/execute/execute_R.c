/**
 * @file execute_R.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail R type format instructions for RISC-V ISA
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author Drew Seidel (dseidel@pdx.edu)
 * @author Stephen Short (steshort@pdx.edu)
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include "execute.h"
#include "../registers/registers.h"

// R Type Instructions
void addInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Add Instruction, rd = rs1 + rs2 = %d + %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] + REG[decInstruction.rs2]);
	#endif
	
	// Overflow ignored, rd = rs1 + rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] + REG[decInstruction.rs2]);
	
}

void subInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Sub Instruction, rd = rs1 - rs2 = %d - %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] - REG[decInstruction.rs2]);
	#endif
	
	// Overflow ignored, rd = rs1 - rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] - REG[decInstruction.rs2]);
}

void andInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("And Instruction, rd = rs1 & rs2 = %d & %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] & REG[decInstruction.rs2]);
	#endif
	
	//rd = rs1 & rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] & REG[decInstruction.rs2]);
}

void orInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Or Instruction, rd = rs1 | rs2 = %d | %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] | REG[decInstruction.rs2]);
	#endif
	
	// rd = rs1 | rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] | REG[decInstruction.rs2]);
}

void xorInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("Xor Instruction, rd = rs1 ^ rs2 = %d ^ %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], REG[decInstruction.rs1] ^ REG[decInstruction.rs2]);
	#endif
	
	//rd = rs1 ^ rs2;
	registers_write(decInstruction.rd, REG[decInstruction.rs1] ^ REG[decInstruction.rs2]);
}

void sltInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %d, rs2 = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2]);
	#endif
	
	//SLT instruction	
	if (REG[decInstruction.rs1] < REG[decInstruction.rs2])
	 	registers_write(decInstruction.rd, 1); 
	else
	 	registers_write(decInstruction.rd, 0); 
}

void sltuInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SLT, rd = %d, rs1 = %u, rs2 = %u\n", REG[decInstruction.rd], (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2]);
	#endif
	
	//SLTU instruction. NOTE TEST SLTU rd, x0, rs2 sets rd to 1 if rs2 is not equal to 0
	if (((uint32_t)REG[decInstruction.rs1]) < ((uint32_t) REG[decInstruction.rs2]))
		registers_write(decInstruction.rd, 1);
	else
		registers_write(decInstruction.rd, 0);
}

void sllInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SLL, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
	
	//SLL instruction
	registers_write(decInstruction.rd, REG[decInstruction.rs1] << (REG[decInstruction.rs2] & 0x1F));
}


void srlInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	#ifdef DEBUG
		Printf("SRL, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], REG[decInstruction.rs2] & 0x1F);
	#endif
	
	registers_write(decInstruction.rd, (uint32_t)REG[decInstruction.rs1] >> (REG[decInstruction.rs2] & 0x1F));
}


//todo look into more
void sraInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;
	
	int32_t msb = REG[decInstruction.rs1] & 0x80000000; // filter out all but msb
	uint32_t shamt = REG[decInstruction.rs2] & 0x1F;
	
	#ifdef DEBUG
		Printf("SRA, rd = %d, rs1 = %d, rs2 & 0x1F = %d\n", REG[decInstruction.rd], REG[decInstruction.rs1], shamt);
	#endif
	
	if (msb > 0)
	{
		registers_write(decInstruction.rd, signExtend((decInstruction.rs1 >> shamt), 32-shamt));

	}
	else
	{
		registers_write(decInstruction.rd, REG[decInstruction.rs1] >> shamt);
	}
}



//MUL RV32M standard extension instructions; 

void mulInstruction(instruction_t decInstruction)
{
	extern int32_t *REG;

	int64_t result = (REG[decInstruction.rs1] * REG[decInstruction.rs2]) & 0x00000000FFFFFFFF; 
	result = (int32_t)result; 
	
	#ifdef DEBUG
		Printf("MUL Instruction, rd (lower) = rs1 * rs2 = %d * %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], result);
	#endif
	
	// lower half of result stored in rd, rd = rs1 * rs2;
	registers_write(decInstruction.rd, result);
}

void mulhInstruction(instruction_t decInstruction)
{

	//confusing wording on spec page 43 for below blocked out error check
	/*
	if (decInstruction.rd == decInstruction.rs1 || decInstruction.rd ==decInstruction.rs2)
	{
		Printf("Error. Could not complete instruction.\nMULH, MULHU, MULHSU does not allow rd to be the same as rs1 or rs2\n");
		return;  
	}
	*/

	extern int32_t *REG;

	int64_t result = (int64_t)REG[decInstruction.rs1] * (int64_t)REG[decInstruction.rs2]; 
	result = (uint64_t)result >> 32;  //shift right logical as if unsigned
	result = (int32_t)result; 
	
	#ifdef DEBUG
		Printf("MULH Instruction, rd (higher) = rs1 * rs2 = %d * %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], result);
	#endif
	
	// upper half of result stored in rd, rd = rs1 * rs2;
	registers_write(decInstruction.rd, result);
}


void mulhuInstruction(instruction_t decInstruction)
{

	//confusing wording on spec page 43 for below blocked out error check
	/*if (decInstruction.rd == decInstruction.rs1 || decInstruction.rd ==decInstruction.rs2)
	{
		Printf("Error. Could not complete instruction.\nMULH, MULHU, MULHSU does not allow rd to be the same as rs1 or rs2\n");
		return;  
	}
	*/

	extern int32_t *REG;

	uint64_t result = (uint64_t)((uint32_t)REG[decInstruction.rs1]) * (uint64_t)((uint32_t)REG[decInstruction.rs2]); 
	result = result >> 32;  //shift right logical as if unsigned 
	result = (int32_t)result; 
	
	#ifdef DEBUG
		Printf("MULHU Instruction, rd (higher) = (unsigned)rs1 * (unsigned)rs2 = %u * %u = %u\n", (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2], (uint32_t) result);
	#endif
	
	// upper half of result stored in rd, rd = (unsigned)rs1 * (unsigned)rs2;
	registers_write(decInstruction.rd, result);
}

void mulhsuInstruction(instruction_t decInstruction)
{

	//confusing wording on spec page 43 for below blocked out error check
	/*if (decInstruction.rd == decInstruction.rs1 || decInstruction.rd ==decInstruction.rs2)
	{
		Printf("Error. Could not complete instruction.\nMULH, MULHU, MULHSU does not allow rd to be the same as rs1 or rs2\n");
		return;  
	}
	*/
	extern int32_t *REG;

    uint64_t result = (int64_t)REG[decInstruction.rs1] * (uint64_t)((uint32_t)REG[decInstruction.rs2]);
	result = result >> 32;  //shift right logical as if unsigned
	result = (int32_t)result; 
	
	#ifdef DEBUG
		Printf("MULHSU, rd (higher) = (signed)rs1 * (unsigned)rs2 = %d * %u = %d\n", REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2], result);
	#endif
	
	// upper half of result stored in rd, rd = (signed)rs1 * (unsigned)rs2;
	registers_write(decInstruction.rd, result);
}

void divInstruction(instruction_t decInstruction)
{
	//confusing wording on spec page 44 for below blocked out error check
	/*if (decInstruction.rd == decInstruction.rs1 || decInstruction.rd ==decInstruction.rs2)
	{
		Printf("Error. Could not complete instruction.\nDIV, DIV, REM, REMU does not allow rd to be the same as rs1 or rs2\n");
		return;  
	}
	*/

	extern int32_t *REG;
	int32_t result;

	// Divide by 0, Table 7.1 Implementation 
	if (REG[decInstruction.rs2] == 0)
	{
		result = -1;
		#ifdef DEBUG
			Printf("DIV Instruction (DIVIDE BY 0), rd = rs1 / rs2 = %d / %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], result);
		#endif
	}
	// Overflow, Table 7.1 Implementation
	else if ((REG[decInstruction.rs1] == 0x80000000) && (REG[decInstruction.rs2] == -1))
	{
		result = 0x80000000; //(-2)^31 = -2,147,483,648 The maximum negative number
		#ifdef DEBUG
			Printf("DIV Instruction (OVERFLOW), rd = rs1 / rs2 = %d / %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], result);
		#endif
	}
	else
	{
		result = REG[decInstruction.rs1] / REG[decInstruction.rs2]; 
		#ifdef DEBUG
			Printf("DIV Instruction, rd = rs1 / rs2 = %d / %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], result);
		#endif
	}
	
	registers_write(decInstruction.rd, result);
}

void divuInstruction(instruction_t decInstruction)
{

	//confusing wording on spec page 44 for below blocked out error check
	/*if (decInstruction.rd == decInstruction.rs1 || decInstruction.rd ==decInstruction.rs2)
	{
		Printf("Error. Could not complete instruction.\nDIV, DIV, REM, REMU does not allow rd to be the same as rs1 or rs2\n");
		return;  
	}
	*/

	extern int32_t *REG;
	uint32_t result;

	// Divide by 0/Overflow Table 7.1 Implementation 
	if (REG[decInstruction.rs2] == 0)
	{
		result = 0xFFFFFFFF; // Divide by 0, results in 2^32 - 1 = 4,294,967,295 if unsigned
		#ifdef DEBUG
			Printf("DIVU Instruction (DIVIDE BY 0), rd = (unsigned) rs1 / (unsigned) rs2 = %u / %u = %u\n", (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2], result);
		#endif
	}
	else
	{
		result = (uint32_t) ((uint32_t)REG[decInstruction.rs1] / (uint32_t) REG[decInstruction.rs2]); 
		#ifdef DEBUG
			Printf("DIVU Instruction, rd = (unsigned)rs1 / (unsigned)rs2 = %u / %u = %u\n", (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2], (uint32_t) result);
		#endif
	}

	registers_write(decInstruction.rd, (int32_t) result);
}

void remInstruction(instruction_t decInstruction)
{

	//confusing wording on spec page 44 for below blocked out error check
	/*if (decInstruction.rd == decInstruction.rs1 || decInstruction.rd ==decInstruction.rs2)
	{
		Printf("Error. Could not complete instruction.\nDIV, DIV, REM, REMU does not allow rd to be the same as rs1 or rs2\n");
		return;  
	}
	*/

	extern int32_t *REG;
	int32_t remainder;
	
	// Divide by 0, Table 7.1 Implementation 
	if (REG[decInstruction.rs2] == 0)
	{
		remainder = REG[decInstruction.rs1];
		#ifdef DEBUG
			Printf("REM Instruction (DIVIDE BY 0), rd = rs1 % rs2 = %d % %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], remainder);
		#endif
	}
	// Overflow, Table 7.1 Implementation
	else if ((REG[decInstruction.rs1] == 0x80000000) && (REG[decInstruction.rs2] == -1))
	{
		remainder = 0; 
		#ifdef DEBUG
			Printf("REM Instruction (Overflow), rd = rs1 \% rs2 = %d \% %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], remainder);
		#endif
	}
	else
	{
		remainder = REG[decInstruction.rs1] % REG[decInstruction.rs2]; 
		#ifdef DEBUG
			Printf("REM Instruction, rd = rs1 \% rs2 = %d \% %d = %d\n", REG[decInstruction.rs1], REG[decInstruction.rs2], remainder);
		#endif
	}
	
	registers_write(decInstruction.rd, remainder);
}

void remuInstruction(instruction_t decInstruction)
{

	//confusing wording on spec page 43 for below blocked out error check
	/*if (decInstruction.rd == decInstruction.rs1 || decInstruction.rd ==decInstruction.rs2)
	{
		Printf("Error. Could not complete instruction.\nDIV, DIV, REM, REMU does not allow rd to be the same as rs1 or rs2\n");
		return;  
	}
	*/

	extern int32_t *REG;
	uint32_t remainder;
	
	// Divide by 0, Table 7.1 Implementation 
	if (REG[decInstruction.rs2] == 0)
	{
		remainder = (uint32_t) REG[decInstruction.rs1];
		#ifdef DEBUG
			Printf("REMU Instruction (DIVIDE BY 0), rd = rs1 % rs2 = %u % %u = %u\n", (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2], remainder);
		#endif
	}
	else
	{
		remainder = (uint32_t) ((uint32_t)REG[decInstruction.rs1]) % ((uint32_t) REG[decInstruction.rs2]); 
		#ifdef DEBUG
			Printf("REMU Instruction, rd = rs1 % rs2 = %u % %u = %u\n", (uint32_t) REG[decInstruction.rs1], (uint32_t) REG[decInstruction.rs2], remainder);
		#endif
	}
	
	registers_write(decInstruction.rd, remainder);
}


// END R Type Instructions

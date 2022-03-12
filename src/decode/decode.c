/**
 * @file decode.c
 * @brief Source code for decoding functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author Drew Seidel (dseidel@pdx.edu)
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include "decode.h"
#include "../execute/execute.h"

void decodeInstruction(int32_t rawInstruction, instruction_t *decInstruction)
{
	uint8_t opcodeVal = rawInstruction & 0x7F;
	decode_t instructionType = iTypeDecode(opcodeVal, rawInstruction);
	
	decInstruction->itype = instructionType;
	decInstruction->opcode = opcodeVal;

	switch(decInstruction->itype)
	{
		case R:
			decInstruction->rd        = (uint8_t)  ((rawInstruction & 0xF80)      >>  7); 
			decInstruction->funct3    = (uint8_t)  ((rawInstruction & 0x7000)     >> 12);
			decInstruction->rs1       = (uint8_t)  ((rawInstruction & 0xF8000)    >> 15);
			decInstruction->rs2       = (uint8_t)  ((rawInstruction & 0x1F00000)  >> 20);
			decInstruction->funct7    = (uint8_t)  ((rawInstruction & 0xFE000000) >> 25);
			decInstruction->immediate = 0; // Unused
			decInstruction->instruction = decodeInstruction_R(decInstruction->funct3, decInstruction->funct7);
			break;
		case I:
			decInstruction->rd        = (uint8_t)  ((rawInstruction & 0xF80)      >>  7); 
			decInstruction->funct3    = (uint8_t)  ((rawInstruction & 0x7000)     >> 12);
			decInstruction->rs1       = (uint8_t)  ((rawInstruction & 0xF8000)    >> 15);
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) ((rawInstruction & 0xFFF00000) >> 20);
			decInstruction->instruction = decodeInstruction_I(decInstruction->opcode, decInstruction->funct3, decInstruction->immediate);
			break;
		case S:
			decInstruction->rd        = (uint8_t)   0; // Unused 
			decInstruction->funct3    = (uint8_t)  ((rawInstruction & 0x7000)     >> 12);
			decInstruction->rs1       = (uint8_t)  ((rawInstruction & 0xF8000)    >> 15);
			decInstruction->rs2       = (uint8_t)  ((rawInstruction & 0x1F00000)  >> 20);
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) (((rawInstruction & 0xFE000000) >> 20) + ((rawInstruction & 0xF80) >> 7));
			decInstruction->instruction = decodeInstruction_S(decInstruction->funct3);
			break;
		case U:
			decInstruction->rd        = (uint8_t)  ((rawInstruction & 0xF80)      >>  7); 
			decInstruction->funct3    = (uint8_t)   0; // Unused
			decInstruction->rs1       = (uint8_t)   0; // Unused
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) ((rawInstruction & 0xFFFFF000));
			decInstruction->instruction = decodeInstruction_U(decInstruction->opcode);
			break;
		case B:
			decInstruction->rd        = (uint8_t)   0; // Unused
			decInstruction->funct3    = (uint8_t)  ((rawInstruction & 0x7000)     >> 12);
			decInstruction->rs1       = (uint8_t)  ((rawInstruction & 0xF8000)    >> 15);
			decInstruction->rs2       = (uint8_t)  ((rawInstruction & 0x1F00000)  >> 20);
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t)  ( ((rawInstruction & 0x80000000) >> 19) + ((rawInstruction & 0x80) << 4) + ((rawInstruction & 0x7E000000) >> 20) + ((rawInstruction & 0xF00) >> 7) );
			decInstruction->instruction = decodeInstruction_B(decInstruction->funct3);
			break;
		case J:
			decInstruction->rd        = (uint8_t)  ((rawInstruction & 0xF80)      >>  7);
			decInstruction->funct3    = (uint8_t)   0; // Unused
			decInstruction->rs1       = (uint8_t)   0; // Unused
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t)  ( ((rawInstruction & 0x80000000) >> 11) + (rawInstruction & 0xFF000) + ((rawInstruction & 0x100000) >> 9) + ((rawInstruction & 0x7FE00000) >> 20) );
			decInstruction->instruction = decodeInstruction_J(decInstruction->opcode);
			break;
		case NONE:
			decInstruction->rd        = (uint8_t)   0;
			decInstruction->funct3    = (uint8_t)   0; // Unused
			decInstruction->rs1       = (uint8_t)   0; // Unused
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t)  0;
			decInstruction->instruction = ERROR;
			break;
		default:
			Fprintf(stderr, "Error: Invalid iType, unable to decode the rest of the instructions.\n");
			exit(1);
			break;
	}
	
	// Check that the register reference isn't invalud
	if (decInstruction->rd > 31)
	{
		Fprintf(stderr, "Error in decoded instruction. Invalid rd register = x%d.\n", decInstruction->rd);
		exit(1);
	}
	if (decInstruction->rs1 > 31)
	{
		Fprintf(stderr, "Error in decoded instruction. Invalid rs1 register = x%d.\n", decInstruction->rs1);
		exit(1);
	}
	if (decInstruction->rd > 31)
	{
		Fprintf(stderr, "Error in decoded instruction. Invalid rs2 register = x%d.\n", decInstruction->rs2);
		exit(1);
	}


}

decode_t iTypeDecode(uint8_t opcode, int32_t rawInstruction)
{
	decode_t iType;
	switch(opcode)
	{
		case 0b0110011:
			iType = R;
			break;
		case 0b0010011:
		case 0b1100111:
		case 0b0000011:
		case 0b1110011:
			iType = I;
			break;
		case 0b0100011:
			iType = S;
			break;
		case 0b0110111:
		case 0b0010111:
			iType = U;
			break;
		case 0b1100011:
			iType = B;
			break;
		case 0b1101111:
			iType = J;
			break;
		default:
			// Error
			iType = NONE;
			break;
	}
	return iType;
}

instruction_e_t decodeInstruction_R(uint8_t func3, uint8_t func7)
{
	instruction_e_t determinedInstruction;
	switch(func3)
	{

		case 0b000:
			if      (func7 == 0b0000000)
				determinedInstruction = ADD;
			else if (func7 == 0b0100000)
				determinedInstruction = SUB;
			else if (func7 == 0b0000001)
				determinedInstruction = MUL; 
			else // invalid
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b000 in R-type instruction.\n");
				exit(1);
			}
			break;
		case 0b001:
			if 		(func7 == 0b0000000)
				determinedInstruction = SLL;
			else if (func7 == 0b0000001)
				determinedInstruction = MULH; 
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b001 in R-type instruction.\n");
				exit(1);
			}
			break;
		case 0b010:
			if 		(func7 == 0b0000000)
			determinedInstruction = SLT;
			else if (func7 == 0b0000001)
				determinedInstruction = MULHSU; 
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b010 in R-type instruction.\n");
				exit(1);
			}			
			break;
		case 0b011:
			if 		(func7 == 0b0000000)
			determinedInstruction = SLTU;
			else if (func7 == 0b0000001)
				determinedInstruction = MULHU; 
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b011 in R-type instruction.\n");
				exit(1);
			}						
			break;
		case 0b100:
			if 		(func7 == 0b0000000)
			determinedInstruction = XOR;
			else if (func7 == 0b0000001)
				determinedInstruction = DIV; 
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b100 in R-type instruction.\n");
				exit(1);
			}								
			break;
		case 0b101:
			if      (func7 == 0b0000000)
				determinedInstruction = SRL;
			else if (func7 == 0b0100000)
				determinedInstruction = SRA;
			else if (func7 == 0b0000001)
				determinedInstruction = DIVU; 
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b101 in R-type instruction.\n");
				exit(1);
			}
			break;
		case 0b110:
			if 		(func7 == 0b0000000)
			determinedInstruction = OR;
			else if (func7 == 0b0000001)
				determinedInstruction = REM; 
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b110 in R-type instruction.\n");
				exit(1);
			}						
			break;		
		case 0b111:
			if 		(func7 == 0b0000000)
			determinedInstruction = AND;
			else if (func7 == 0b0000001)
				determinedInstruction = REMU; 
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b111 in R-type instruction.\n");
				exit(1);
			}						
			break;		
		default:
			Fprintf(stderr, "Error determining instruction of type R.\n");
			determinedInstruction = ERROR;
			break;
	}
	return determinedInstruction;
}

instruction_e_t decodeInstruction_I(uint8_t opcode, uint8_t func3, int32_t imm)
{
	instruction_e_t determinedInstruction;
	switch(opcode)
	{
		case 0b0000011:
			if 	(func3 == 0b000)
				determinedInstruction = LB;
			else if (func3 == 0b001)
				determinedInstruction = LH;
			else if (func3 == 0b010)
				determinedInstruction = LW;
			else if (func3 == 0b100)
				determinedInstruction = LBU;
			else if (func3 == 0b101)
				determinedInstruction = LHU;
			else
			{
				Fprintf(stderr, "Error:  Invalid func3 when opcode = 0b0000011 in I-type instruction.\n");
				exit(1);
			}
			break;
		case 0b0010011:
			if 	(func3 == 0b000)
				determinedInstruction = ADDI;
			else if (func3 == 0b001)
				determinedInstruction = SLLI;
			else if (func3 == 0b010)
				determinedInstruction = SLTI;
			else if (func3 == 0b011)
				determinedInstruction = SLTIU;
			else if (func3 == 0b100)
				determinedInstruction = XORI;
			else if (func3 == 0b101)
			{
				imm = imm >> 5;
				if (imm == 0)
					determinedInstruction = SRLI;
				else if (imm == 0x20)
					determinedInstruction = SRAI;
				else
				{
					Fprintf(stderr, "Error: Invalid immediate when opcode = 0b0010011 and func3 = 0b101 in I-type instruction.\n");
					exit (1);
				}
			}
			else if (func3 == 0b110)
				determinedInstruction = ORI;
			else if (func3 == 0b111)
				determinedInstruction = ANDI;
			else
			{
				Fprintf(stderr, "Error: Invalid func3 when opcode = 0b0010011 in I-type instruction.\n");
				exit(1);
			}
			break;
		case 0b1100111:
			determinedInstruction = JALR;
			break;
		case 0b1110011:
			if (imm == 0)
				determinedInstruction = ECALL;
			else if (imm == 1)
				determinedInstruction = EBREAK;
			else
			{
				Fprintf(stderr, "Error: invalid immediate when opcode = 0b1110011 in I-type instruction.\n");
				exit(1);
			}
			break;
		default:
			Fprintf(stderr, "Error determining instruction of type I.\n");
			determinedInstruction = ERROR;
			break;
	}
	return determinedInstruction;
}

instruction_e_t decodeInstruction_S(uint8_t func3)
{
	instruction_e_t determinedInstruction;
	switch(func3)
	{

		case 0b000:
			determinedInstruction = SB;
			break;
		case 0b001:
			determinedInstruction = SH;
			break;
		case 0b010:
			determinedInstruction = SW;
			break;
		default:
			Fprintf(stderr, "Error determining instruction of type S.\n");
			determinedInstruction = ERROR;
			break;
	}
	return determinedInstruction;
}

instruction_e_t decodeInstruction_U(uint8_t opcode)
{
	instruction_e_t determinedInstruction;
	switch(opcode)
	{

		case 0b0010111:
			determinedInstruction = AUIPC;
			break;
		case 0b0110111:
			determinedInstruction = LUI;
			break;
		default:
			Fprintf(stderr, "Error determining instruction of type U.\n");
			determinedInstruction = ERROR;
			break;
	}
	return determinedInstruction;
}

instruction_e_t decodeInstruction_B(uint8_t func3)
{
	instruction_e_t determinedInstruction;
	switch(func3)
	{

		case 0b000:
			determinedInstruction = BEQ;
			break;
		case 0b001:
			determinedInstruction = BNE;
			break;
		case 0b100:
			determinedInstruction = BLT;
			break;
		case 0b101:
			determinedInstruction = BGE;
			break;
		case 0b110:
			determinedInstruction = BLTU;
			break;
		case 0b111:
			determinedInstruction = BGEU;
			break;
		default:
			Fprintf(stderr, "Error determining instruction of type B.\n");
			determinedInstruction = ERROR;
			break;
	}
	return determinedInstruction;
}

instruction_e_t decodeInstruction_J(uint8_t opcode)
{
	instruction_e_t determinedInstruction;
	switch(opcode)
	{
		case 0b1101111:
			determinedInstruction = JAL;
			break;
		default:
			Fprintf(stderr, "Error determining instruction of type J.\n");
			determinedInstruction = ERROR;
	}
	return determinedInstruction;
}

void errorTypeDecode(int32_t rawInstruction)
{
	extern uint32_t PC;
	Fprintf(stderr, "Error: Invalid opcode, unable to decode instruction encoding type.\n");
	Fprintf(stderr, "PC = 0x%.8X, raw instruction = 0x%.8X\n", PC, rawInstruction);
	//TODO Update this error function
	//garbageCollection();
	exit(1);
}

void printInstructionSimple(instruction_t *decInstruction)
{
	extern uint32_t PC;
	Printf("PC = 0x%.8X, Instruction = %s\nrs1 = %d, rs2 = %d, Rd = %d, immediate = %d\n", PC, instructionEnumToStr(decInstruction->instruction), decInstruction->rs1, decInstruction->rs2, decInstruction->rd, decInstruction->immediate);
}

void printInstruction(instruction_t *decInstruction)
{
	extern int32_t *REG;
	
	// Create binary strings
	char *binaryfunct7String = Malloc(sizeof(char) * 8);
	intto7Bin(decInstruction->funct7, binaryfunct7String);
	
	char *binaryopcodeString = Malloc(sizeof(char) * 8);
	intto7Bin(decInstruction->opcode, binaryopcodeString);
	
	char *binaryfunct3String = Malloc(sizeof(char) * 4);
	intto3Bin(decInstruction->funct3, binaryfunct3String);
	
	switch(decInstruction->itype)
	{
		case R:
			Printf("Encoding Type	: R\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("rd Register  	: %2u = 0x%.8X\n", decInstruction->rd, REG[decInstruction->rd]);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %2u = 0x%.8X\n", decInstruction->rs1, REG[decInstruction->rs1]);
			Printf("rs2 Register	: %2u = 0x%.8X\n", decInstruction->rs2, REG[decInstruction->rs2]);
			Printf("funct7		: 0b%s\n", binaryfunct7String);
			break;
		case I:
			Printf("Encoding Type	: I\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("rd Register  	: %2u = 0x%.8X\n", decInstruction->rd, REG[decInstruction->rd]);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %2u = 0x%.8X\n", decInstruction->rs1, REG[decInstruction->rs1]);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case S:
			Printf("Encoding Type	: S\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %2u = 0x%.8X\n", decInstruction->rs1, REG[decInstruction->rs1]);
			Printf("rs2 Register	: %2u = 0x%.8X\n", decInstruction->rs2, REG[decInstruction->rs2]);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case U:
			Printf("Encoding Type	: U\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("rd Register  	: %2u = 0x%.8X\n", decInstruction->rd, REG[decInstruction->rd]);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case B:
			Printf("Encoding Type	: B\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %2u = 0x%.8X\n", decInstruction->rs1, REG[decInstruction->rs1]);
			Printf("rs2 Register	: %2u = 0x%.8X\n", decInstruction->rs2, REG[decInstruction->rs2]);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case J:
			Printf("Encoding Type	: J\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("rd Register  	: %2u = 0x%.8X\n", decInstruction->rd, REG[decInstruction->rd]);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		default:
			Printf("Invalid Instruction Encoding Type\n");
			break;
	}
	Printf("\n");
	free(binaryfunct7String);
	free(binaryopcodeString);
	free(binaryfunct3String);
}

void printAssembly(FILE *fd, int32_t opcode)
{
	instruction_t instruction;
	decodeInstruction(opcode, &instruction);
	switch (instruction.itype)
	{
		case (R):
			Fprintf(fd, "%s\t%d, %d, %d\n", instructionEnumToStr(instruction.instruction), instruction.rd, instruction.rs1, instruction.rs2);
			break;
		case (I):
			Fprintf(fd, "%s\t%d, %d, %d\n", instructionEnumToStr(instruction.instruction), instruction.rd, instruction.rs1, signExtend(instruction.immediate, 11));
			break;
		case (S):
			Fprintf(fd, "%s\t%d, %d(%d)\n", instructionEnumToStr(instruction.instruction), instruction.rs2, signExtend(instruction.immediate, 11), instruction.rs1);
			break;
		case (U):
			Fprintf(fd, "%s\t%d, %d\n", instructionEnumToStr(instruction.instruction), instruction.rd, instruction.immediate<<12);
			break;
		case (B):
			Fprintf(fd, "%s\t%d, %d, %d\n", instructionEnumToStr(instruction.instruction), instruction.rs1, instruction.rs2, signExtend(instruction.immediate<<1, 12));
			break;
		case (J):
			Fprintf(fd, "%s\t%d, %d\n", instructionEnumToStr(instruction.instruction), instruction.rd, signExtend(instruction.immediate<<1, 20));
			break;
		case (NONE):
			Fprintf(fd, "...\n");
			break;
	}
}

const char *instructionEnumToStr(instruction_e_t instruction)
{
	switch(instruction)
	{
		case ERROR:
			return "ERROR";
			break;
		case LUI:
			return "LUI";
			break;
		case AUIPC:
			return "AUIPC";
			break;
		case JAL:
			return "JAL";
			break;
		case JALR:
			return "JALR";
			break;
		case BEQ:
			return "BEQ";
			break;
		case BNE:
			return "BNE";
			break;
		case BLT:
			return "BLT";
			break;
		case BGE:
			return "BGE";
			break;
		case BLTU:
			return "BLTU";
			break;
		case BGEU:
			return "BGEU";
			break;
		case LB:
			return "LB";
			break;
		case LH:
			return "LH";
			break;
		case LW:
			return "LW";
			break;
		case LBU:
			return "LBU";
			break;
		case LHU:
			return "LHU";
			break;
		case SB:
			return "SB";
			break;
		case SH:
			return "SH";
			break;
		case SW:
			return "SW";
			break;
		case ADDI:
			return "ADDI";
			break;
		case SLTI:
			return "SLTI";
			break;
		case SLTIU:
			return "SLTIU";
			break;
		case XORI:
			return "XORI";
			break;
		case ORI:
			return "ORI";
			break;
		case ANDI:
			return "ANDI";
			break;
		case SLLI:
			return "SLLI";
			break;
		case SRLI:
			return "SRLI";
			break;
		case SRAI:
			return "SRAI";
			break;
		case ADD:
			return "ADD";
			break;
		case SUB:
			return "SUB";
			break;
		case SLL:
			return "SLL";
			break;
		case SLT:
			return "SLT";
			break;
		case SLTU:
			return "SLTU";
			break;
		case XOR:
			return "XOR";
			break;
		case SRL:
			return "SRL";
			break;
		case SRA:
			return "SRA";
			break;
		case OR:
			return "OR";
			break;
		case AND:
			return "AND";
			break;
		case MUL: 
			return "MUL"; 
			break; 
		case MULH:
			return "MULH";
			break; 
		case MULHSU:
			return "MULHSU";
			break; 
		case MULHU:
			return "MULHU";
			break; 
		case DIV:
			return "DIV"; 
			break; 
		case DIVU: 
			return "DIVU"; 
			break; 
		case REM: 
			return "REM"; 
			break; 
		case REMU:
			return "REMU"; 
			break; 
		case ECALL:
			return "ECALL";
			break;
		case EBREAK:
			return "EBREAK";
			break;
		default:
			return "INVALID ERROR";
			break;
	}
	return "ERROR";
}

void intto7Bin(uint8_t value, char *binaryString)
{	
	char immediateString[8] = "0000000\0";
	uint32_t mask = 0x40;
	for (uint32_t i = 0; i != 7; i++)
	{
		if ((value & mask) > 0)
		{
			immediateString[i] = '1';
		}
		mask = mask >> 1;
	}
	strncpy(binaryString, immediateString, 8);
}

void intto3Bin(uint8_t value, char *binaryString)
{	
	char immediateString[4] = "000\0";
	uint32_t mask = 0x4;
	for (uint32_t i = 0; i != 3; i++)
	{
		if ((value & mask) > 0)
		{
			immediateString[i] = '1';
		}
		mask = mask >> 1;
	}
	
	strncpy(binaryString, immediateString, 4);
}

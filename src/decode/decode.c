/**
 * @file decode.c
 * @brief Source code for decoding functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author TODO
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include "decode.h"

void decodeInstruction(int32_t rawInstruction, instruction_t *decInstruction)
{
	uint8_t opcodeVal = rawInstruction & 0x7F;
	decode_t instructionType = iTypeDecode(opcodeVal);
	
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
			decInstruction->immediate = (uint8_t)  (((rawInstruction & 0x1F00000)  >> 20) & 0x1F); // Unused
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
			decInstruction->immediate = (uint32_t) (((rawInstruction & 0xFFF00000) >> 20) + ((rawInstruction & 0xF80) >> 7));
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

decode_t iTypeDecode(uint8_t opcode)
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
			errorTypeDecode();
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
			else // invalid
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b000 in R-type instruction.\n");
				exit(1);
			}
			break;
		case 0b001:
			determinedInstruction = SLL;
			break;
		case 0b010:
			determinedInstruction = SLT;
			break;
		case 0b011:
			determinedInstruction = SLTU;
			break;
		case 0b100:
			determinedInstruction = XOR;
			break;
		case 0b101:
			if      (func7 == 0b0000000)
				determinedInstruction = SRL;
			else if (func7 == 0b0100000)
				determinedInstruction = SRA;
			else
			{
				Fprintf(stderr, "Error: Invalid func7 when func3 = 0b101 in R-type instruction.\n");
				exit(1);
			}
			break;
		case 0b110:
			determinedInstruction = OR;
			break;
		case 0b111:
			determinedInstruction = AND;
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

void errorTypeDecode(void)
{
	Fprintf(stderr, "Error: Invalid opcode, unable to decode instruction encoding type.\n");
	//TODO Update this error function
	//garbageCollection();
	exit(1);
}

void printInstructionSimple(instruction_t *decInstruction)
{
	extern uint32_t PC;
	Printf("PC = 0x%.8X, Instruction = %s\n", PC, instructionEnumToStr(decInstruction->instruction));
}

void printInstruction(instruction_t *decInstruction)
{
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
			Printf("rd Register  	: %u\n", decInstruction->rd);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %u\n", decInstruction->rs1);
			Printf("rs2 Register	: %u\n", decInstruction->rs2);
			Printf("funct7		: 0b%s\n", binaryfunct7String);
			break;
		case I:
			Printf("Encoding Type	: I\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("rd Register  	: %u\n", decInstruction->rd);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %u\n", decInstruction->rs1);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case S:
			Printf("Encoding Type	: S\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %u\n", decInstruction->rs1);
			Printf("rs2 Register	: %u\n", decInstruction->rs2);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case U:
			Printf("Encoding Type	: U\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("rd Register  	: %u\n", decInstruction->rd);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case B:
			Printf("Encoding Type	: B\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("funct3		: 0b%s\n", binaryfunct3String);
			Printf("rs1 Register	: %u\n", decInstruction->rs1);
			Printf("rs2 Register	: %u\n", decInstruction->rs2);
			Printf("immediate (hex)	: 0x%.8X = %d\n", decInstruction->immediate, decInstruction->immediate);
			break;
		case J:
			Printf("Encoding Type	: J\n");
			Printf("Instruction  	: %s\n", instructionEnumToStr(decInstruction->instruction));
			Printf("Opcode       	: 0b%s\n", binaryopcodeString);
			Printf("rd Register  	: %u\n", decInstruction->rd);
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
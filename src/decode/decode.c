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
#include "../wrappers/wrappers.h"

void decodeInstruction(int32_t rawInstruction, instructionPtr_t decInstruction)
{
	uint8_t opcodeVal = rawInstruction & 0x7F;
	decode_t instructionType = iTypeDecode(opcodeVal);

	switch(instructionType)
	{
		case R:
			decInstruction->rd        = (uint8_t)  (rawInstruction & 0xF80)      >>  7; 
			decInstruction->funct3    = (uint8_t)  (rawInstruction & 0x7000)     >> 12;
			decInstruction->rs1       = (uint8_t)  (rawInstruction & 0xF8000)    >> 15;
			decInstruction->rs2       = (uint8_t)  (rawInstruction & 0x1F00000)  >> 20;
			decInstruction->funct7    = (uint8_t)  (rawInstruction & 0xFE000000) >> 25;
			decInstruction->immediate = (uint32_t)  0; // Unused
			decInstruction->instruction = decodeInstruction_R(decInstruction->funct3, decInstruction->funct7);
			break;
		case I:
			decInstruction->rd        = (uint8_t)  (rawInstruction & 0xF80)      >>  7; 
			decInstruction->funct3    = (uint8_t)  (rawInstruction & 0x7000)     >> 12;
			decInstruction->rs1       = (uint8_t)  (rawInstruction & 0xF8000)    >> 15;
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) (rawInstruction & 0xFFF00000) >> 20;
			decInstruction->instruction = decodeInstruction_I(opcodeVal, decInstruction->funct3, decInstruction->immediate);
			break;
		case S:
			decInstruction->rd        = (uint8_t)   0; // Unused 
			decInstruction->funct3    = (uint8_t)  (rawInstruction & 0x7000)     >> 12;
			decInstruction->rs1       = (uint8_t)  (rawInstruction & 0xF8000)    >> 15;
			decInstruction->rs2       = (uint8_t)  (rawInstruction & 0x1F00000)  >> 20;
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) (((rawInstruction & 0xFFF00000) >> 20) + ((rawInstruction & 0xF80) >> 7));
			decInstruction->instruction = decodeInstruction_S(decInstruction->funct3);
			break;
		case U:
			decInstruction->rd        = (uint8_t)  (rawInstruction & 0xF80)      >>  7; 
			decInstruction->funct3    = (uint8_t)   0; // Unused
			decInstruction->rs1       = (uint8_t)   0; // Unused
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) (rawInstruction & 0xFFFFF000);
			decInstruction->instruction = decodeInstruction_U(decInstruction->opcode);
			break;
		case B:
			decInstruction->rd        = (uint8_t)   0; // Unused
			decInstruction->funct3    = (uint8_t)  (rawInstruction & 0x7000)     >> 12;
			decInstruction->rs1       = (uint8_t)  (rawInstruction & 0xF8000)    >> 15;
			decInstruction->rs2       = (uint8_t)  (rawInstruction & 0x1F00000)  >> 20;
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t)  ( ((rawInstruction & 0x80000000) >> 19) + ((rawInstruction & 0x80) << 4) + ((rawInstruction & 0x7E000000) >> 20) + ((rawInstruction & 0xF00) >> 7) );
			decInstruction->instruction = decodeInstruction_B(decInstruction->funct3);
			break;
		case J:
			decInstruction->rd        = (uint8_t)  (rawInstruction & 0xF80)      >>  7;
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
	}

	decInstruction->itype = instructionType;
	decInstruction->opcode = opcodeVal;

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
				if (((imm & 0x000) >> 5) == 0)
					determinedInstruction = SRLI;
				else if (((imm & 0x400) >> 5) == 0x20)
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
			Fprintf(stderr, "Error: Invalid opcode for I-type instruction.\n");
			exit(1);	
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
			Fprintf(stderr, "Error: invalid funct3 field for S-type instruction.\n");
			exit(1);
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
			Fprintf(stderr, "Error: invalid opcode field for U-type instruction.\n");
			exit(1);
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
			Fprintf(stderr, "Error: invalid funct3 field for B-type instruction.\n");
			exit(1);
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
			Fprintf(stderr, "Error: invalid opcode field for J-type instruction.\n");
			exit(1);
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

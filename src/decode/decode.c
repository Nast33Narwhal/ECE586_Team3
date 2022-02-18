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
#include <ctype.h>
#include <stdbool.h>

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
			break;
		case I:
			decInstruction->rd        = (uint8_t)  (rawInstruction & 0xF80)      >>  7; 
			decInstruction->funct3    = (uint8_t)  (rawInstruction & 0x7000)     >> 12;
			decInstruction->rs1       = (uint8_t)  (rawInstruction & 0xF8000)    >> 15;
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) (rawInstruction & 0xFFF00000) >> 20;
			break;
		case S:
			decInstruction->rd        = (uint8_t)   0; // Unused 
			decInstruction->funct3    = (uint8_t)  (rawInstruction & 0x7000)     >> 12;
			decInstruction->rs1       = (uint8_t)  (rawInstruction & 0xF8000)    >> 15;
			decInstruction->rs2       = (uint8_t)  (rawInstruction & 0x1F00000)  >> 20;
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) (((rawInstruction & 0xFFF00000) >> 20) + ((rawInstruction & 0xF80) >> 7));
			break;
		case U:
			decInstruction->rd        = (uint8_t)  (rawInstruction & 0xF80)      >>  7; 
			decInstruction->funct3    = (uint8_t)   0; // Unused
			decInstruction->rs1       = (uint8_t)   0; // Unused
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t) (rawInstruction & 0xFFFFF000);
			break;
		case B:
			decInstruction->rd        = (uint8_t)   0; // Unused
			decInstruction->funct3    = (uint8_t)  (rawInstruction & 0x7000)     >> 12;
			decInstruction->rs1       = (uint8_t)  (rawInstruction & 0xF8000)    >> 15;
			decInstruction->rs2       = (uint8_t)  (rawInstruction & 0x1F00000)  >> 20;
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t)  ( ((rawInstruction & 0x80000000) >> 19) + ((rawInstruction & 0x80) << 4) + ((rawInstruction & 0x7E000000) >> 20) + ((rawInstruction & 0xF00) >> 7) )
			break;
		case B:
			decInstruction->rd        = (uint8_t)  (rawInstruction & 0xF80)      >>  7;
			decInstruction->funct3    = (uint8_t)   0; // Unused
			decInstruction->rs1       = (uint8_t)   0; // Unused
			decInstruction->rs2       = (uint8_t)   0; // Unused
			decInstruction->funct7    = (uint8_t)   0; // Unused
			decInstruction->immediate = (uint32_t)  ( ((rawInstruction & 0x80000000) >> 11) + (rawInstruction & 0xFF000) + ((rawInstruction & 0x100000) >> 9 + ((rawInstruction & 0x7FE00000) >> 20) )
			break;
		default:
			Fprintf(stderr, "Error: Invalid iType, unable to decode the rest of the instructions.\n");
			printRegisters();
			exit(1);
	}

	decInstruction->itype = instructionType;
	decInstruction->opcode = opcodeVal;

}

decode_t itypeDecode(uint8_t opcode)
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

void errorTypeDecode(void)
{
	Fprintf(stderr, "Error: Invalid opcode, unable to decode instruction encoding type.\n");
	//TODO Update this error function
	printRegisters();
	//garbageCollection();
	exit(1);
}

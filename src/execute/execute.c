/**
 * @file execute.c
 * @brief Source code for executing functions for RV32I Instruction Simulator
 *
 * @detail TODO
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

/**
 * @fn      signExtend
 * @brief   Sign extends a value to 32 bits
 *
 * @param   value   Value to sign extend
 * @param   msb     Position of the MSB, starting at bit 0
 * @returns 32-bit sign extended number
 */
static int32_t signExtend(int32_t value, uint8_t msb);

void executeInstruction(instruction_t decInstruction)
{	
	switch(decInstruction.instruction)
	{
		case ERROR:
			Fprintf(stderr, "Error: Executing Instruction with ERROR type instruction.\n");
			break;
		case LUI:
			luiInstruction(decInstruction);
			break;
		case AUIPC:
			auipcInstruction(decInstruction);
			break;
		case JAL:
			jalInstruction(decInstruction);
			break;
		case JALR:
			jalrInstruction(decInstruction);
			break;
		case BEQ:
			beqInstruction(decInstruction);
			break;
		case BNE:
			bneInstruction(decInstruction);
			break;
		case BLT:
			bltInstruction(decInstruction);
			break;
		case BGE:
			bgeInstruction(decInstruction);
			break;
		case BLTU:
			bltuInstruction(decInstruction);
			break;
		case BGEU:
			bgeuInstruction(decInstruction);
			break;
		case LB:
			lbInstruction(decInstruction);
			break;
		case LH:
			lhInstruction(decInstruction);
			break;
		case LW:
			lwInstruction(decInstruction);
			break;
		case LBU:
			lbuInstruction(decInstruction);
			break;
		case LHU:
			lhuInstruction(decInstruction);
			break;		
		case SB:
			sbInstruction(decInstruction);
			break;
		case SH:
			shInstruction(decInstruction);
			break;
		case SW:
			swInstruction(decInstruction);
			break;		 
		case ADDI:
			addiInstruction(decInstruction);
			break;
		case SLTI:
			sltiInstruction(decInstruction);
			break;
		case SLTIU:
			sltiuInstruction(decInstruction);
			break;
		case XORI:
			xoriInstruction(decInstruction);
			break;
		case ORI:
			oriInstruction(decInstruction);
			break;
		case ANDI:
			andiInstruction(decInstruction);
			break;
		case SLLI:
			slliInstruction(decInstruction);
			break;
		case SRLI:
			srliInstruction(decInstruction);
			break;
		case SRAI:
			sraiInstruction(decInstruction);
			break;
		case ADD:
			addInstruction(decInstruction);
			break;
		case SUB:
			subInstruction(decInstruction);
			break;
		case SLL:
			sllInstruction(decInstruction);
			break;
		case SLT:
			sltInstruction(decInstruction); 
			break;
		case SLTU:
			sltuInstruction(decInstruction); 
			break;
		case XOR:
			xorInstruction(decInstruction);
			break;
		case SRL:
			srlInstruction(decInstruction);
			break;
		case SRA:
			sraInstruction(decInstruction);
			break;
		case OR:
			orInstruction(decInstruction); 
			break;
		case AND:
			andInstruction(decInstruction);
		case MUL: 
			 mulInstruction(decInstruction); 
			break; 
		case MULH:
			 mulhInstruction(decInstruction); 
			break; 
		case MULHSU:
			 mulhsuInstruction(decInstruction); 
			break; 
		case MULHU:
			 mulhuInstruction(decInstruction); 
			break; 
		case DIV:
			 divInstruction(decInstruction);
			break; 
		case DIVU: 
			 divuInstruction(decInstruction);
			break; 
		case REM: 
			remInstruction(decInstruction); 
			break; 
		case REMU:
			remuInstruction(decInstruction); 
			break;
		case ECALL:
			Printf("ECALL instruction execution function not implemented yet\n");
			break;
		case EBREAK:
			Printf("EBREAK instruction execution function not implemented yet\n");
			break;
		default:
			Fprintf(stderr, "Error: Executing Instruction with no valid type instruction.\n");
			break;
	}
}

int32_t signExtend(int32_t value, uint8_t msb)
{
	if (value & (1<<msb))
	{
		return (value | (0xFFFFFFFF << msb));
	}
	return value;
}

#include "execute_BJ.c"
#include "execute_I.c"
#include "execute_R.c"
#include "execute_SU.c"

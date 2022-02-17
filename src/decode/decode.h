/**
 * @file decode.h
 * @brief Header code for decoding functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author TODO
 *
 */

#ifndef _DECODE_H
#define _DECODE_H

#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// encoding type enum for RV32I, can be expanded for Multiply and Floating Point
#ifndef DECODE_T_
#define DECODE_T_
typedef enum _decode_e {R, I, S, U, B, J} decode_t;
#endif

typedef struct _instruction_s
{
	decode_t itype;
	uint8_t	 opcode;
	uint8_t  rd;
	uint8_t  funct3;
	uint8_t  rs1;
	uint8_t  rs2;
	uint8_t  funct7;
	uint32_t immediate; // Store shamt here, too

} instruction_t, *instructionPtr_t;

/**
 * @fn TODO
 * @brief TODO
 *
 * @detail TODO
 *
 * @param TODO
 * @returns TODO
 *
 */


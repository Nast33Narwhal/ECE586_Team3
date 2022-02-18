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
	 int32_t immediate; // Store shamt here, too

} instruction_t, *instructionPtr_t;

/**
 * @fn decodeInstruction
 * @brief function to decode the instruction, determines the type and corresponding values
 *
 * @detail Finds instruction type, opcode, registers, any function codes, and any immediates.
 *
 * @param rawInstruction - 32 bit integer
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
 void decodeInstruction(int32_t rawInstruction, instructionPtr_t decInstruction);



/**
 * @fn itypeDecode
 * @brief Decodes opcode and returns the instruction encoding type
 *
 * @detail outputs instruction type based on the opcode
 *
 * @param opcode - 7 bit opcode stored in uint8_t
 * @returns decode_t enumeration holding the different encoding types
 *
 */
decode_t itypeDecode(uint8_t opcode);


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


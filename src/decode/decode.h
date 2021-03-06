/**
 * @file decode.h
 * @brief Header code for decoding functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author Drew Seide (dseidel@pdx.edu)
 *
 */

#ifndef _DECODE_H
#define _DECODE_H

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../wrappers/wrappers.h"

// encoding type enum for RV32I, can be expanded for Multiply and Floating Point
#ifndef DECODE_T_
#define DECODE_T_
typedef enum _decode_e {R, I, S, U, B, J, NONE} decode_t;
#endif

// instruction enum for all of the possible instructions encoded in RV32I
#ifndef INSTRUCTION_ENUM_T_
#define INSTRUCTION_ENUM_T_
typedef enum _instruction_e {ERROR, LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND, ECALL, EBREAK, MUL, MULH, MULHSU, MULHU, DIV, DIVU, REM, REMU} instruction_e_t;
#endif

#ifndef INSTRUCTION_T_
#define INSTRUCTION_T_
typedef struct _instruction_s
{
	decode_t 	itype;
	instruction_e_t instruction;
	uint8_t		opcode;
	uint8_t 	rd;
	uint8_t 	funct3;
	uint8_t 	rs1;
	uint8_t 	rs2;
	uint8_t 	funct7;
	int32_t 	immediate; // Store shamt here, too

} instruction_t, *instructionPtr_t;
#endif

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
 * @param rawInstruction - In case there is an error, prints out the raw encoded instruction
 * @returns decode_t enumeration holding the different encoding types
 *
 */
decode_t iTypeDecode(uint8_t opcode, int32_t rawInstruction);

/**
 * @fn decodeInstruction_R
 * @brief determines the actual instruction from an R-type encoded instruction
 *
 * @detail Using the decoded information, determines the actual instruction
 *
 * @param func3 field
 * @param func7 field
 * @returns instruction_e_t enumerated value
 *
 */
instruction_e_t decodeInstruction_R(uint8_t func3, uint8_t func7);

/**
 * @fn decodeInstruction_I
 * @brief determines the actual instruction from an I-type encoded instruction
 *
 * @detail Using the decoded information, determines the actual instruction
 *
 * @param opcode field
 * @param func3 field
 * @param imm field
 * @returns instruction_e_t enumerated value
 *
 */
instruction_e_t decodeInstruction_I(uint8_t opcode, uint8_t func3, int32_t imm);

/**
 * @fn decodeInstruction_S
 * @brief determines the actual instruction from an S-type encoded instruction
 *
 * @detail Using the decoded information, determines the actual instruction
 *
 * @param func3 field
 * @returns instruction_e_t enumerated value
 *
 */
instruction_e_t decodeInstruction_S(uint8_t func3);

/**
 * @fn decodeInstruction_U
 * @brief determines the actual instruction from an U-type encoded instruction
 *
 * @detail Using the decoded information, determines the actual instruction
 *
 * @param opcode field
 * @returns instruction_e_t enumerated value
 *
 */
instruction_e_t decodeInstruction_U(uint8_t opcode);

/**
 * @fn decodeInstruction_B
 * @brief determines the actual instruction from an B-type encoded instruction
 *
 * @detail Using the decoded information, determines the actual instruction
 *
 * @param func3 field
 * @returns instruction_e_t enumerated value
 *
 */
instruction_e_t decodeInstruction_B(uint8_t func3);

/**
 * @fn decodeInstruction_J
 * @brief determines the actual instruction from an J-type encoded instruction
 *
 * @detail Using the decoded information, determines the actual instruction
 *
 * @param opcode field
 * @returns instruction_e_t enumerated value
 *
 */
instruction_e_t decodeInstruction_J(uint8_t opcode);


/**
 * @fn errorTypeDecode
 * @brief error function when unable to determine type
 *
 * @detail prints errors
 *
 * @param rawInstruction - in the event that an error occurs, prints the hex info on the instruction
 * @returns void
 *
 */
void errorTypeDecode(int32_t rawInstruction);


/**
 * @fn printInstruction
 * @brief prints the current instruction in hex from memory and the decoded instruction values 
 *
 * @detail Prints all of the information about the decoded instruction based on type
 *
 * @param instructionPtr_t decInstruction holds all of the instruction information
 * @returns void
 *
 */
void printInstruction(instructionPtr_t decInstruction);

/**
 * @fn printInstructionSimple
 * @brief prints the PC and Instruction Name 
 *
 * @detail Prints just the PC in hex and the Instruction Name
 *
 * @param instructionPtr_t decInstruction holds all of the instruction information
 * @returns void
 *
 */
void printInstructionSimple(instruction_t *decInstruction);

/**
 * @fn		printAssembly
 * @brief 	Converts machine code into assembly and prints it to a file
 * 
 * @param 	fd		File descriptor to write to
 * @param 	opcode	Machine code to translate
 */
void printAssembly(FILE *fd, int32_t opcode);

/**
 * @fn instructionEnumToStr
 * @brief Takes in the enumerated instruction and returns a char* string for printing
 *
 * @detail Prints out the instruction
 *
 * @param instruction_e_t enumerated instruction
 * @returns char * string
 *
 */
const char *instructionEnumToStr(instruction_e_t instruction);

/**
 * @fn intto7Bin
 * @brief Converts integer into 7 bit binary string
 *
 * @detail Allows user to signify the number of bits to return as a string
 *
 * @param int32_t value to convert
 * @returns char * string
 *
 */
void intto7Bin(uint8_t value, char *binaryString);

/**
 * @fn intto3Bin
 * @brief Converts integer into 3 bit binary string
 *
 * @detail Allows user to signify the number of bits to return as a string
 *
 * @param int32_t value to convert
 * @returns char * string
 *
 */
void intto3Bin(uint8_t value, char *binaryString);


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
#endif

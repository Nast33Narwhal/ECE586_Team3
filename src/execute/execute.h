/**
 * @file execute.h
 * @brief Header code for executing functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author TODO
 *
 */

#ifndef _EXECUTE_H
#define _EXECUTE_H

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../decode/decode.h"

/**
 * @fn executeInstruction
 * @brief function to execute the correct instruction based on the passed instruction
 *
 * @detail Based on instruction, calls the correct function to effect the registers and PC as appropriate
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void executeInstruction(instruction_t decInstruction);


/**
 * @fn addInstruction
 * @brief executes the add instruction
 *
 * @detail rd = rs1+rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void addInstruction(instruction_t decInstruction);


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

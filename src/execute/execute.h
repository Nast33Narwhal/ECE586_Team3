/**
 * @file execute.h
 * @brief Header code for executing functions for RV32I Instruction Simulator
 *
 * @detail TODO
 *
 * @date Presented TODO
 *
 * @author Braden Harwood (bharwood@pdx.edu)
 * @author Drew Seidel    (dseidel@pdx.edu)
 * @author Stephen Short  (steshort@pdx.edu)
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
#include "../memory/memory.h"

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
 * @fn luiInstruction
 * @brief executes the function: load upper immediate
 *
 * @detail Places upper 20 bits into the destination reg. filling lower 12 bits with 0s
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void luiInstruction(instruction_t decInstruction);


/**
 * @fn auipcInstruction
 * @brief executes the function: add upper immediate to pc
 *
 * @detail adds upper 20 bits of immediate field to upper 20 bits of PC
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void auipcInstruction(instruction_t decInstruction);


/**
 * @fn jalInstruction
 * @brief executes the function: jump and link
 *
 * @detail 20 bits of immediate field are sign extended and added to jal instruction address as new target address.
 *         pc + 4 is saved in the register rd
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void jalInstruction(instruction_t decInstruction);


/**
 * @fn jalrInstruction
 * @brief executes the function: jump and link register
 *
 * @detail 12 bit immediate added to register field rs1 and LSBit set to 0, creating the target address.
 *         Address following JALR command is saved as pc + 4 in register rd.
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void jalrInstruction(instruction_t decInstruction);


/**
 * @fn beqInstruction
 * @brief executes the function: branch if equal
 *
 * @detail The 12 bit immediate field (sign extended to two-bit offset) is added to address of branch instruction for target address.
 *          Condition: registers rs1 and rs2 are equal
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void beqInstruction(instruction_t decInstruction);


/**
 * @fn bneInstruction
 * @brief executes the function: branch if not equal
 *
 * @detail The 12 bit immediate field (sign extended to two-bit offset) is added to address of branch instruction for target address.
 *          Condition: registers rs1 and rs2 are unequal
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void bneInstruction(instruction_t decInstruction);


/**
 * @fn bltInstruction
 * @brief executes the function: branch if less than
 *
 * @detail Creates a delicious sandwich consisting of fresh bread, crisply bacon, lettuce, and a tomato if rs1 is less than rs2
 *         The 12 bit SIGNED immediate field (sign extended to two-bit offset) is added to address of branch instruction for target address.
 *          Condition: registers rs1 is less than rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void bltInstruction(instruction_t decInstruction);


/**
 * @fn bgeInstruction
 * @brief executes the function: branch if greater than
 *
 * @detail The 12 bit SIGNED immediate field (sign extended to two-bit offset) is added to address of branch instruction for target address.
 *          Condition: registers rs1 is greater than rs2.
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void bgeInstruction(instruction_t decInstruction);



/**
 * @fn bltuInstruction
 * @brief executes the function: branch if less than unsigned
 *
 * @detail The 12 bit UNSIGNED immediate field (sign extended to two-bit offset) is added to address of branch instruction for target address.
 *          Condition: registers rs1 is less than rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void bltuInstruction(instruction_t decInstruction);


/**
 * @fn bgeuInstruction
 * @brief executes the function: branch if greater than unsigned
 *
 * @detail The 12 bit UNSIGNED immediate field (sign extended to two-bit offset) is added to address of branch instruction for target address.
 *          Condition: registers rs1 is greater than rs2.
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void bgeuInstruction(instruction_t decInstruction);


/**
 * @fn lbInstruction
 * @brief executes the function: load byte
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The lower 8 bits of contents of the target address are stored
 *          in register rd. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void lbInstruction(instruction_t decInstruction);


/**
 * @fn lhInstruction
 * @brief executes the function: load half word
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The lower 16 bits of contents of the target address are stored
 *          in register rd. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void lhInstruction(instruction_t decInstruction);


/**
 * @fn lwInstruction
 * @brief executes the function: load word
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The contents of the target address are stored
 *          in register rd. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void lwInstruction(instruction_t decInstruction);


/**
 * @fn lbuInstruction
 * @brief executes the function: load byte upper
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The lower 8 bits of contents of the target address are stored
 *          in register rd after being sign extended. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void lbuInstruction(instruction_t decInstruction);


/**
 * @fn lhuInstruction
 * @brief executes the function: load half word upper
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The lower 16 bits of contents of the target address are stored
 *          in register rd after being sign extended. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void lhuInstruction(instruction_t decInstruction);


/**
 * @fn sbInstruction
 * @brief executes the function: store byte
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The lower 8 bits of contents of rs2 are stored
 *          in the target address. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sbInstruction(instruction_t decInstruction);


/**
 * @fn shInstruction
 * @brief executes the function: store half word
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The lower 16 bits of contents of rs2 are stored
 *          in the target address. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void shInstruction(instruction_t decInstruction);


/**
 * @fn swInstruction
 * @brief executes the function: store word
 *
 * @detail  The 12 bit sign-extended imm. field is added to rs1 to create the target address. The contents of rs2 are stored
 *          in the target address. 
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void swInstruction(instruction_t decInstruction);

/**
 * @fn addiInstruction
 * @brief executes the function: add immediate
 *
 * @detail The 12 bit immediate field is added to register rs1 and the result is stored in rd. rd = rs1 + imm
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void addiInstruction(instruction_t decInstruction);


/**
 * @fn sltiInstruction
 * @brief executes the function: set less than immediate
 *
 * @detail If register rs1 is less than the sign extended SIGNED immediate field, rd is set to 1.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sltiInstruction(instruction_t decInstruction);


/**
 * @fn sltiuInstruction
 * @brief executes the function: set less than immediate unsigned
 *
 * @detail If register rs1 is less than the sign extended UNSIGNED immediate field, rd is set to 1.
           Also, if rs1 is equal to 0, than rd is set to 1.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sltiuInstruction(instruction_t decInstruction);


/**
 * @fn xoriInstruction
 * @brief executes the function: xor immediate
 *
 * @detail Register rs1 is xor'd with the sign extended 12 bit immediate field and the result is stored in rd.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void xoriInstruction(instruction_t decInstruction);


/**
 * @fn oriInstruction
 * @brief executes the function: or immediate
 *
 * @detail Register rs1 is or'd with the sign extended 12 bit immediate field and the result is stored in rd.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void oriInstruction(instruction_t decInstruction);


/**
 * @fn andiInstruction
 * @brief executes the function: and immediate
 *
 * @detail Register rs1 is and'd with the sign extended 12 bit immediate field and the result is stored in rd.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void andiInstruction(instruction_t decInstruction);


/**
 * @fn slliInstruction
 * @brief executes the function: shift logical left immediate
 *
 * @detail The contents of rs1 are shifted left by the amount encoded in the lower 5 bits of the 12 bit immediate field.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void slliInstruction(instruction_t decInstruction);


/**
 * @fn srliInstruction
 * @brief executes the function: shift logical right immediate
 *
 * @detail The contents of rs1 are shifted right by the amount encoded in the lower 5 bits of the 12 bit immediate field.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void srliInstruction(instruction_t decInstruction);


/**
 * @fn sraiInstruction
 * @brief executes the function: shift right arithmetic immediate
 *
 * @detail The contents of rs1 are shifted right by the amount encoded in the lower 5 bits of the 12 bit immediate field and sign bit is saved.
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sraiInstruction(instruction_t decInstruction);


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
 * @fn subInstruction
 * @brief executes the subtract instruction
 *
 * @detail rd = rs1-rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void subInstruction(instruction_t decInstruction);

/**
 * @fn sllInstruction
 * @brief executes the shift left logical instruction
 *
 * @detail rd = rs1 << rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sllInstruction(instruction_t decInstruction);


/**
 * @fn sltInstruction
 * @brief executes the set less than instruction
 *
 * @detail rd = (rs1 < rs2) ? 1 : 0;
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sltInstruction(instruction_t decInstruction);


/**
 * @fn sltuInstruction
 * @brief executes the unsigned set less than instruction
 *
 * @detail rd = ((uint32_t) rs1 < (uint32_t) rs2) ? 1 : 0;
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sltuInstruction(instruction_t decInstruction);


/**
 * @fn xorInstruction
 * @brief executes the xor instruction
 *
 * @detail rd = rs1 ^ rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void xorInstruction(instruction_t decInstruction);


/**
 * @fn srlInstruction
 * @brief executes the shift right logical instruction
 *
 * @detail rd = rs1 >> rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void srlInstruction(instruction_t decInstruction);


/**
 * @fn sraInstruction
 * @brief executes the shift right arithmetic instruction
 *
 * @detail (if msb == 1) rd = ((rs1 >> rs2) | (0xFFFFFFFF << rs2)) else rd = rs1 >> rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void sraInstruction(instruction_t decInstruction);


/**
 * @fn orInstruction
 * @brief executes the or instruction
 *
 * @detail rd = rs1 | rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void orInstruction(instruction_t decInstruction);


/**
 * @fn andInstruction
 * @brief executes the and instruction
 *
 * @detail rd = rs1 & rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void andInstruction(instruction_t decInstruction);


/**
 * @fn mulInstruction
 * @brief executes the mul instruction
 *
 * @detail rd gets the lower 32 bits of = rs1 * rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void mulInstruction(instruction_t decInstruction);


/**
 * @fn mulhInstruction
 * @brief executes the mulh instruction
 *
 * @detail rd gets the upper 32 bits of = rs1 * rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void mulhInstruction(instruction_t decInstruction);


/**
 * @fn mulhuInstruction
 * @brief executes the mulhu instruction
 *
 * @detail rd gets the upper 32 bits of = (unsigned)rs1 * (unsigned)rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void mulhuInstruction(instruction_t decInstruction);


/**
 * @fn mulhsuInstruction
 * @brief executes the mulhsu instruction
 *
 * @detail rd gets the upper 32 bits of = (unsigned)rs1 * (unsigned)rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void mulhsuInstruction(instruction_t decInstruction);


/**
 * @fn divInstruction
 * @brief executes the div instruction
 *
 * @detail rd gets signed(rs1) / rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void divInstruction(instruction_t decInstruction);


/**
 * @fn divuInstruction
 * @brief executes the divu instruction
 *
 * @detail rd gets unsigned(rs1) / rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void divuInstruction(instruction_t decInstruction);


/**
 * @fn remInstruction
 * @brief executes the rem instruction
 *
 * @detail rd gets signed(rs1) % rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void remInstruction(instruction_t decInstruction);


/**
 * @fn remuInstruction
 * @brief executes the remu instruction
 *
 * @detail rd gets unsigned(rs1) % rs2
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void remuInstruction(instruction_t decInstruction);


/**
 * @fn ecallInstruction
 * @brief executes the ecall instruction
 *
 * @detail System call
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void ecallInstruction(instruction_t decInstruction);


/**
 * @fn ebreakInstruction
 * @brief executes the ebreak instruction
 *
 * @detail System call
 *
 * @param decInstruction - instruction_t passed by reference to be updated
 * @returns void
 *
 */
void ebreakInstruction(instruction_t decInstruction);

/**
 * @fn      signExtend
 * @brief   Sign extends a value to 32 bits
 *
 * @param   value   Value to sign extend
 * @param   msb     Position of the MSB, starting at bit 0
 * @returns 32-bit sign extended number
 */
int32_t signExtend(int32_t value, uint8_t msb);

/**
 * @fn      TODO
 * @brief   TODO
 *
 * @details TODO
 *
 * @param   TODO
 * @returns TODO
 */

#endif

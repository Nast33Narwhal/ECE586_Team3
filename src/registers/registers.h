/**
 * @file	registers.h
 * @brief	functions to initilze and handle registers
 * @desc    TBD
 *
 *          ECE 486/586 Final Project, Dr. Mark Faust
 *          Portland State University, Winter 2022
 *
 * @date Presented TBA
 *
 * @author  Stephen Short   (steshort@pdx.edu)
 * @author  Drew Seidel     (dseidel@pdx.edu)
 * @author  Michael Weston  (miweston@pdx.edu)
 * @author  Braden Harwood  (bharwood@pdx.edu)
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


//not currently being used 
/* 
typedef struct {
        
 
     int pc;   
     int zero;                       //x0
     int ra;                        //x1
     int sp;                        //x2
     int gp;                        //x3
     int tp;                        //x4
     int t0;                        //x5
     int t1;                        //x6
     int t2;                        //x7
     int s0;                        //x8
     int s1;                        //x9
     int a0;                        //x10
     int a1;                        //x11
     int a2;                        //x12
     int a3;                        //x13
     int a4;                        //x14
     int a5;                        //x15
     int a6;                        //x16
     int a7;                        //x17
     int s2;                        //x18
     int s3;                        //x19
     int s4;                        //x20
     int s5;                        //x21
     int s6;                        //x22
     int s7;                        //x23
     int s8;                        //x24
     int s9;                        //x25
     int s10;                       //x26
     int s11;                       //x27
     int t3;                        //x28
     int t4;                        //x29
     int t5;                        //x30
     int t6;                        //x31
        
} registers_t, *registersPtr_t;
*/

/**
 * @fn		registers_init()
 * @brief	     Initilizes the SP, ZERO register, RA
 *
 * @param 
 * @return	If sucsessful, SP, ZERO, and RA are initilized to zero
 */

int32_t* registers_init();

/**
 * @fn         registers_write
 * @brief      Writes data into a register
 * 
 * @details    Writes the provided data into the specified register in the provided
 *             register file.
 * @param      regNum    The number of the specific register to overwrite (0-31)
 * @param      data      The data to write into the register.
 * @note       Data is not sign extended within this method.
 */
void registers_write(uint8_t regNum, uint32_t data);

/**
 * @fn         regNumToStr
 * 
 * @param      regNum  Register number
 * @return     String with the register's name 
 */
const char *regNumToStr(uint8_t regNum);

/**
 * @fn         printRegisters
 * @brief      Prints out the registers and their values
 * 
 * @details    Writes the registers and the values held to stdout
 *
 */
void printRegisters();

/**
 * @fn         printRegisters_Debug shows
 * @brief      Prints out the registers and their values. Red if the register value was just changed.
 * 
 * @details    Writes the registers and the values held to stdout
 *
 */
void printRegisters_Debug(uint8_t regNum); 
#endif

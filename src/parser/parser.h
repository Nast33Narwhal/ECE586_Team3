/**
 * @file parser.h
 * @brief Input Parser ADT header file
 *
 * @detail 	This header file contains all of the constants, enums, structs, and function prototypes
 *		used for the input parser.
 *		ECE 486/586 Final Project, Dr. Mark Faust
 *		Portland State University,  Winter 2022
 *
 * @date	Presented December 6th, 2021
 *
 * @author	Stephen Short	(steshort@pdx.edu)
 * @author	Drew Seidel	    (dseidel@pdx.edu)
 * @author	Michael Weston 	(miweston@pdx.edu)
 * @author	Braden Harwood 	(bharwood@pdx.edu)
 * 		
 */
#ifndef _PARSER_H
#define _PARSER_H


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_ARRAY 16384

void parseMemFile(char *fileName); 

#endif

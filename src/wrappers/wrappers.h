/**
 * @file	wrappers.h
 * @brief	Helper wrapper functions to catch errors from system calli
 * @desc    Wrapper header file which encompasses the standard system calls: printf,
 *          fprintf, malloc, fopen, and fclose into wrapper functions (first letter capitalized
 *          to differentiate) in order to standardize the exit codes from all errors in the 
 *          memory controller simulator.
 *
 *          ECE 486/586 Final Project, Dr. Mark Faust
 *          Portland State University, Fall 2021
 *
 * @date TBA
 *
 * @author  Stephen Short   (steshort@pdx.edu)
 * @author  Drew Seidel     (dseidel@pdx.edu)
 * @author  Michael Weston  (miweston@pdx.edu)
 * @author  Braden Harwood  (bharwood@pdx.edu)
 */

#ifndef WRAPPERS_H_
#define WRAPPERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @fn		Printf
 * @brief	Wrapper function for printf to catch errors
 *
 * @param	format	A format string provided to printf
 * @param	...	All other variables required for the given format string
 */
void Printf(char* format, ...);

/**
 * @fn		Fprintf
 * @brief	Wrapper function for fprintf to catch errors
 *
 * @param	stream	fd of the target output file
 * @param	format	A format string provided to printf
 * @param	...	All other variables required for the given format string
 */
void Fprintf(FILE* stream, char* format, ...);

/**
 * @fn		Malloc
 * @brief	Wrapper function for malloc
 *
 * @param	size	Size of memory to be allocated
 * @return	Pointer to new memory
 */
void *Malloc(size_t size);

/**
 * @fn		Fopen
 * @brief	Wrapper function for fopen
 *
 * @param	pathname path to filename to open
 * @param	mode	 mode you wish to use with opened file
 * @return	Point to File
 */
FILE *Fopen(const char *pathname, const char *mode);

/**
 * @fn		Fopen
 * @brief	Wrapper function for fopen
 *
 * @param	stream  FILE pointer to be closed
 */
void Fclose(FILE *stream);

/**
 * @fn		isNumber
 * @brief	Checks if a given string contains only numeric digits
 *
 * @param	test	String being examined
 *
 * @return	true if the string only contains numeric digits, false otherwise
 */
bool isNumber(const char* test);

#endif

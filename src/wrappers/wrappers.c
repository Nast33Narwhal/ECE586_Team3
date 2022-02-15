/**
 * @file	wrappers.c
 * @brief	Simple wrapper functions to catch errors from system calls
 * @detail  This source code encompasses all the system calls used in the memory simulator.
 *          The system calls are "wrapped" by these functions so that error checking
 *          can be implemented. This helps to standardize the method of exiting the program
 *          due to an error by allowing the exit code to be assigned for these system calls.          
 *          
 *          ECE 485/585 Final Project, Dr. Mark Faust
 *          Portland State University, Fall 2021
 *
 * @date Presented December 6th, 2021
 *
 * @author  Stephen Short   (steshort@pdx.edu)
 * @author  Drew Seidel (dseidel@pdx.edu)
 * @author  Michael Weston  (miweston@pdx.edu)
 * @author  Braden Harwood  (bharwood@pdx.edu)
 *
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void Printf(char* format, ...)
{

	va_list args;
	va_start (args, format);
	int result = vprintf(format, args);
	va_end(args);

	if (result < 0) //If the print was not successful, alert user via stderr, collect garbage, and exit
	{
		perror("Error calling printf()");
		exit(EXIT_FAILURE);
	}
}

void Fprintf(FILE* stream, char* format, ...)
{
	va_list args;
	va_start (args, format);
	int result = vfprintf(stream, format, args);
	va_end(args);

	if (result < 0) //If the print was not successful, alert user via stderr and exit
	{
		perror("Error calling fprintf()");
		exit(EXIT_FAILURE);
	}
}

void *Malloc(size_t size)
{
	void* newPtr = malloc(size);
	if (newPtr == NULL)
	{
		perror("Error calling malloc()");
		exit(EXIT_FAILURE);
	}
	return newPtr;
}

FILE *Fopen(const char *pathname, const char *mode)
{
	FILE *newFilePtr = fopen(pathname, mode);
	if (newFilePtr == NULL)
	{
		perror("Error calling fopen()");
		exit(EXIT_FAILURE);
	}
	return newFilePtr;
}

void Fclose(FILE *stream)
{
	int returnCode = fclose(stream);
	if (returnCode != 0)
	{
		perror("Error calling fclose()");
		exit(EXIT_FAILURE);
	}
}

bool isNumber(const char* test)
{
	if (!test)
		return false;
	//Check if every character in test is a digit
	if (strspn(test, "0123456789") == strlen(test))
	{
		return true;
	}
	return false;
}

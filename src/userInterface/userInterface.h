

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <stdbool.h>

/**
 * @fn      displayUserInterface
 * @brief   Displays the user interface to stdout and prompts for user input
 * 
 * @param   singleStep  Pointer to single step flag in main simulation. If set to
 *                      true. Then the simulation will call this method again prior
 *                      to the next instruction.
 */
void displayUserInterface(bool *singleStep);

/**
 * @fn      displayHelp
 * @brief   Lists the available commands for the user 
 */
void displayHelp(void);

#endif
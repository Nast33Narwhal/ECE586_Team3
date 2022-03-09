
#include <string.h>
#include <stdio.h>
#include "userInterface.h"
#include "../wrappers/wrappers.h"
#include "../memory/memory.h"
#include "../decode/decode.h"

void displayUserInterface(bool *singleStep)
{  
    char *input = NULL;
    size_t inputSize = 0;
    char cmd[50];
    unsigned arg1;
    unsigned arg2;
    char extra[20];
    *singleStep = false;

    while (1)
    {
        Printf("Enter command:");
        getline(&input, &inputSize, stdin);
        while (input[0] == '\n')
            getline(&input, &inputSize, stdin); //ignore newlines

        Sscanf(input, "%50s ", cmd);
        if ((strcmp(cmd, "h")==0) || (strcmp(cmd, "help")==0))
        {
            displayHelp();
        }
        else if ((strcmp(cmd, "r")==0) || (strcmp(cmd, "run")==0))
        {
            free(input);
            return; //break condition set by loop, but don't want to print "unknown command"
        }
        else if ((strcmp(cmd, "s")==0) || (strcmp(cmd, "step")==0))
        {
            *singleStep = true;
            free(input);
            return;    
        }
        else if ((strcmp(cmd, "b")==0) || (strcmp(cmd, "break")==0))
        {
            if (Sscanf(input, "%50s %64u%20s", cmd, &arg1, extra) == 2 ||
                Sscanf(input, "%50s %64x%20s", cmd, &arg1, extra) == 2)
            {
                if (arg1/4 > mem_getSize())
                {
                    Printf("Breakpoint too large! Maximum address is 0x%08X\n", mem_getSize()*4); 
                    continue; 
                }
                else{
                    if (isBreakpoint(arg1/4))
                    {
                        clrBreakpoint(arg1/4);
                        Printf("Breakpoint cleared at 0x%08X\n", arg1 & 0xFFFFFFFC); //Force word alignment
                    }
                    else
                    {
                        setBreakpoint(arg1/4);
                        Printf("Breakpoint set at 0x%08X\n", arg1 & 0xFFFFFFFC);
                    } 
                }
            }
            else
            {
                Printf("Format is \"break <address>\"\n");
            }
        }
        else if ((strcmp(cmd, "m")==0) || (strcmp(cmd, "mem")==0))
        {
            if (Sscanf(input, "%50s %64u%20s", cmd, &arg1, extra) == 2 ||
                Sscanf(input, "%50s %64x%20s", cmd, &arg1, extra) == 2)
            {
                if (arg1/4 > mem_getSize())
                {
                    Printf("Address too large! Maximum address is 0x%08X\n", mem_getSize()*4); 
                    continue; 
                }
                Printf("0x%08X : 0x%08X\n", arg1 & 0xFFFFFFFC, readMemory(arg1/4));
            }
            else if (Sscanf(input, "%50s %64u-%64u%20s", cmd, &arg1, &arg2, extra) == 3 ||
                        Sscanf(input, "%50s %64x-%64x%20s", cmd, &arg1, &arg2, extra) == 3)
            {
                if (arg1/4 > mem_getSize() || arg2/4 > mem_getSize())
                {
                    Printf("Address too large! Maximum address is 0x%08X\n", mem_getSize()*4); 
                    continue; 
                }
                for (unsigned i = arg1/4; i <= arg2/4; i++)
                {
                    Printf("0x%08X : 0x%08X\n", i*4, readMemory(i));
                }
            }
            else
            {
                Printf("Formats of mem command:\nmem <address>\nmem <start_address>-<stop_address>\n");
            }
        }
        else
        {
            Printf("Unknown command \"%s\" Type \"h\" or \"help\" for a list of commands.\n", cmd);
        }
    }
}

void displayHelp()
{
    Printf("List of available commands:");
    Printf("run, help, mem, step, break\n");
}
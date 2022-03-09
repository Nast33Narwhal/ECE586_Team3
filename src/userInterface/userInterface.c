
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
    unsigned arg;
    char extra[20];
    *singleStep = false;

    while (1)
    {
        Printf("Enter command:");
        getline(&input, &inputSize, stdin);
        while (input[0] == '\n')
            getline(&input, &inputSize, stdin); //ignore newlines
        switch(Sscanf(input, "%50s %64u%20s", cmd, &arg, extra))
        {
            case 1:
                if ((strcmp(cmd, "h")==0) || (strcmp(cmd, "help")==0))
                {
                    displayHelp();
                }
                else if ((strcmp(cmd, "r")==0) || (strcmp(cmd, "run")==0))
                {
                    return; //break condition set by loop, but don't want to print "unknown command"
                }
                else if ((strcmp(cmd, "s")==0) || (strcmp(cmd, "step")==0))
                {
                    *singleStep = true;
                    free(input);
                    return;    
                }
                else
                {
                    Printf("Unknown command \"%s\" Type \"h\" or \"help\" for a list of commands.\n", cmd);
                }
                break;
            case 2:
                if ((strcmp(cmd, "b")==0) || (strcmp(cmd, "break")==0))
                {                    
                    if (arg/4 > mem_getSize())
                    {
                        Printf("Breakpoint too large! Maximum address is 0x%08X\n", mem_getSize()*4); 
                        continue; 
                    }
                    else{
                        if (isBreakpoint(arg/4))
                        {
                            clrBreakpoint(arg/4);
                            Printf("Breakpoint cleared at 0x%08X\n", arg & 0xFFFFFFFC); //Force word alignment
                        }
                        else
                        {
                            setBreakpoint(arg/4);
                            Printf("Breakpoint set at 0x%08X\n", arg & 0xFFFFFFFC);
                        } 
                    }
                }
                else
                {
                    Printf("Unknown command \"%s\" Type \"h\" or \"help\" for a list of commands.\n", cmd);
                }
                break;
            case 3:
                Sscanf(input, "%50s %64x", cmd, &arg);
                if ((strcmp(cmd, "b")==0) || (strcmp(cmd, "break")==0))
                { 
                    if (arg/4 > mem_getSize())
                    {
                        Printf("Breakpoint too large! Maximum address is 0x%08X\n", mem_getSize()*4); 
                        continue; 
                    }
                    else{
                        if (isBreakpoint(arg/4))
                        {
                            clrBreakpoint(arg/4);
                            Printf("Breakpoint cleared at 0x%08X\n", arg & 0xFFFFFFFC); //Force word alignment
                        }
                        else
                        {
                            setBreakpoint(arg/4);
                            Printf("Breakpoint set at 0x%08X\n", arg & 0xFFFFFFFC);
                        } 
                    }
                }
                else
                {
                    Printf("Unknown command \"%s\" Type \"h\" or \"help\" for a list of commands.\n", cmd);
                }
        }        
    }
}

void displayHelp()
{
    Printf("List of available commands:");
    Printf("run, help, step, break\n");
}

#include <string.h>
#include <stdio.h>
#include "userInterface.h"
#include "../wrappers/wrappers.h"
#include "../memory/memory.h"
#include "../decode/decode.h"

void displayUserInterface()
{
    extern uint32_t PC; 
    char cmd[128] = "\0";
    while (strcmp(cmd, "run") && strcmp(cmd, "r"))
    {
        Printf("Enter command:");
        if(Scanf("%128s", cmd))
        {
            if ((strcmp(cmd, "h")==0) || (strcmp(cmd, "help")==0))
            {
                displayHelp();
            }
            else if ((strcmp(cmd, "r")==0) || (strcmp(cmd, "run")==0))
            {
                continue; //break condition set by loop, but don't want to print "unknown command"
            }
            else if ((strcmp(cmd, "s")==0) || (strcmp(cmd, "step")==0)){
                setBreakpoint((PC + 4)/4); 
                break;    
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
    Printf("run, help, step\n");
}
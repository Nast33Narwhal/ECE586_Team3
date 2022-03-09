
#include <string.h>
#include <stdio.h>
#include "userInterface.h"
#include "../wrappers/wrappers.h"
#include "../memory/memory.h"
#include "../decode/decode.h"

#define MEM_SIZE 16384

void displayUserInterface()
{
    extern uint32_t PC; 
    uint32_t breakpoint = 0; 
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
            else if ((strcmp(cmd, "s")==0) || (strcmp(cmd, "step")==0))
            {
                setBreakpoint((PC + 4)/4); 
                break;    
            }
            else if ((strcmp(cmd, "b")==0) || (strcmp(cmd, "break")==0))
            {
                Printf("Enter breakpoint location:"); 
                Scanf("%u", &breakpoint); 
                
                if (breakpoint > MEM_SIZE * 4)
                {
                    Printf("Breakpoint too large!\n"); 
                    continue; 
                }
                else if (breakpoint % 4 != 0)
                {
                    Printf("Breakpoint must be aligned (divisible by four)\n"); 
                    continue;  
                }
                else if (breakpoint <= PC)
                {
                    Printf("Breakpoint must be greater than the current PC\n"); 
                    continue; 
                }
                else{
                    setBreakpoint(breakpoint/4); 
                    break; 
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
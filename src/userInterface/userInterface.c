
#include <string.h>
#include <stdio.h>
#include "userInterface.h"
#include "../wrappers/wrappers.h"
#include "../memory/memory.h"
#include "../decode/decode.h"

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
                Printf("Enter breakpoint location(in hex):"); 
                Scanf("%x", &breakpoint); 
                
                if (breakpoint/4 > mem_getSize())
                {
                    Printf("Breakpoint too large! Maximum address is 0x%08X\n", mem_getSize()*4); 
                    continue; 
                }
                else{
                    if (isBreakpoint(breakpoint/4))
                    {
                        clrBreakpoint(breakpoint/4);
                        Printf("Breakpoint cleared at 0x%08X\n", breakpoint & 0xFFFFFFFC); //Force word alignment
                    }
                    else
                    {
                        setBreakpoint(breakpoint/4);
                        Printf("Breakpoint set at 0x%08X\n", breakpoint & 0xFFFFFFFC);
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
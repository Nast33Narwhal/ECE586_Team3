
#include <string.h>
#include <stdio.h>
#include "userInterface.h"
#include "../registers/registers.h"
#include "../wrappers/wrappers.h"
#include "../memory/memory.h"

void displayUserInterface(bool *singleStep)
{  
    extern uint32_t PC;
    char *input = NULL;
    size_t inputSize = 0;
    char cmd[50];
    unsigned arg1;
    unsigned arg2;
    char extra[20];
    *singleStep = false;

    Printf("PC = 0x%08X : ", PC);
    printAssembly(stdout, readMemory((unsigned)PC/4));

    while (1)
    {
        Printf("Enter command:");
        getline(&input, &inputSize, stdin);
        while (input[0] == '\n')
            getline(&input, &inputSize, stdin); //ignore newlines

        Sscanf(input, "%50s ", cmd);
        //Help
        if ((strcmp(cmd, "h")==0) || (strcmp(cmd, "help")==0))
        {
            displayHelp();
        }
        //Run
        else if ((strcmp(cmd, "r")==0) || (strcmp(cmd, "run")==0))
        {
            free(input);
            return; //break condition set by loop, but don't want to print "unknown command"
        }
        //Single step
        else if ((strcmp(cmd, "s")==0) || (strcmp(cmd, "step")==0))
        {
            *singleStep = true;
            free(input);
            return;    
        }
        //Display register contents
        else if (!strcmp(cmd, "reg"))
        {
            printRegisters();
        }
        //Set/clear a breakpoint
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
        //Set/clear watchpoints
        else if ((strcmp(cmd, "w")==0) || (strcmp(cmd, "watch")==0))
        {
            if (Sscanf(input, "%50s %64u%20s", cmd, &arg1, extra) == 2 ||
                Sscanf(input, "%50s %64x%20s", cmd, &arg1, extra) == 2)
            {
                if (arg1/4 > mem_getSize())
                {
                    Printf("Watchpoint too large! Maximum address is 0x%08X\n", mem_getSize()*4); 
                    continue; 
                }
                else{
                    if (isWatchpoint(arg1/4))
                    {
                        clrWatchpoint(arg1/4);
                        Printf("Watchpoint cleared at 0x%08X\n", arg1 & 0xFFFFFFFC); //Force word alignment
                    }
                    else
                    {
                        setWatchpoint(arg1/4);
                        Printf("Watchpoint set at 0x%08X\n", arg1 & 0xFFFFFFFC);
                    } 
                }
            }
            else
            {
                Printf("Format is \"watch <address>\"\n");
            }
        }
        //Display memory
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
                Printf("0x%08X : 0x%08X\t\t", arg1 & 0xFFFFFFFC, readMemory(arg1/4));
                printAssembly(stdout, readMemory(arg1/4));
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
                    Printf("0x%08X : 0x%08X\t\t", i*4, readMemory(i));
                    printAssembly(stdout, readMemory(i));
                }
            }
            else
            {
                Printf("Formats of mem command:\nmem <address>\nmem <start_address>-<stop_address>\n");
            }
        }
        //Everything else
        else
        {
            Printf("Unknown command \"%s\" Type \"h\" or \"help\" for a list of commands.\n", cmd);
        }
    }
}

void displayHelp()
{
    Printf("List of available commands:");
    Printf("run, help, mem, reg, step, break, watch\n\n");
    Printf("run:\nRuns the simulator until a breakpoint is reached (if one is set).\n\n");
    Printf("mem:\nPrints out a provided memory address(es) (i.e. \"mem <address>\" or \"mem <start address>-<end address>\" for multiple addresses).\n\n");
    Printf("reg:\nPrints out current values of all registers.\n\n");
    Printf("step:\nExecutes the next decoded command in the simulation from the provided .mem file.\n\n");
    Printf("break:\nSets a breakpoint at a provided memory location (i.e. \"break <address>\").\n\n");
    Printf("watch:\nSets a watchpoint at a provided memory location (i.e. \"watch <address>).\n\n");
}

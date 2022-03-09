
#include <string.h>
#include <stdio.h>
#include "userInterface.h"
#include "../wrappers/wrappers.h"

void displayUserInterface()
{
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
    Printf("run, help\n");
}
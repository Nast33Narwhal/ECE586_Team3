#include<stdio.h>


//int global = 0; 

int main(){

    
    for(int i = 3; i <= 6; i++)
    {
        for(int j = 0; j <= 6; j++)
        {
            if (i > j)
            {
                __asm__("addi t4, x0, 1");     //x8 gets 1 if i is greater than j. others cleared
                __asm__("addi t5, x0, 0");
                __asm__("addi t6, x0, 0"); 

            }
                
            else if (i == j)
            {
                __asm__("addi t4, x0, 0");     //gets 1 if i is equal to j. others cleared
                __asm__("addi t5, x0, 1");
                __asm__("addi t6, x0, 0"); 
            }
                
            else 
            {
            
                __asm__("addi t4, x0, 0");    //x10 gets 1  if i is less than j. others cleared
                __asm__("addi t5, x0, 0");
                __asm__("addi t6, x0, 1"); 
            }
             
        }

    }

    // I am an idiot 
    /*for(unsigned int i = -6; i <= 6; i++)
    {
        for(int j = 0; j <= 6; j++)
        {
            if (i > j)
                branch_greater(); 
            else if (i == j)
                branch_equal(); 
            else if (i < j)
                branch_less(); 
            else
            {
                continue; 
            }
        }
        
    }
    */

    return 0; 
}



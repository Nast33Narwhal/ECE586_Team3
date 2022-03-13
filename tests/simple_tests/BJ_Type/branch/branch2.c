#include<stdio.h>


void branch_greater(); 
void branch_equal(); 
void branch_less(); 

//int global = 0; 

int main(){

    
    for(int i = 3; i <= 6; i++)
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

void branch_greater(){

    /* asm("addi x8, x0, 1");     //x8 gets 1 if i is greater than j. others cleared
     asm("addi x9, x0, 0x00000000");
     asm("addi x10, x0, 0x00000000"); */
     int local = 1;  
 }

 void branch_equal(){

    /* asm("addi x9, x0, 1");     //gets 1 if i is equal to j. others cleared
     asm("addi x8, x0, 0x00000000");
     asm("addi x10, x0, 0x00000000"); */
     int local = 2; 

 }

 void branch_less(){

     /*asm("addi x10, x0, 1");    //x10 gets 1  if i is less than j. others cleared
     asm("addi x8, x0, 0x00000000");
     asm("addi x9, x0, 0x00000000"); */
     int local = 3; 

 }

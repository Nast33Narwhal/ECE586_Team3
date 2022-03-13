#include<stdio.h>


void branch_greater(); 
void branch_equal(); 
void branch_less(); 

int global = 0; 

int main(){

    
    for(int i = -6; i <= 6; i++)
    {
        for(int j = 0; j <= 6; i++)
        {
            if (i > j)
                branch_greater(); 
            else if (i == j)
                branch_equal(); 
            else if (i < j)
                branch_less(); 
            else
            {
                //nothing
            }
        }

    }

    for(unsigned int i = -6; i <= 6; i++)
    {
        for(int j = 0; j <= 6; i++)
        {
            if (i > j)
                branch_greater(); 
            else if (i == j)
                branch_equal(); 
            else if (i < j)
                branch_less(); 
            else
            {
                //nothing
            }
        }

    }

    return 0; 
}

void branch_greater(){

    global = 1; //global gets 1 if greater than case 
    
}

void branch_equal(){

    global = 2;     //global gets 2 if equal case

}

void branch_less(){

    global = 3;     //global gets 3 if less than case 

}

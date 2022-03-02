#include <stdio.h>

int main(){

//ADD tests

int a = 5; 
int b = 6; 
int c = a + b;  

int d = -5; 
int e = 6; 
int f = d + e; 

int h = -10; 
int i = -10; 
int j = h + i; 
long long int x = 0xF000; 
long long int y = 0xFFFFFFFFF; 
long long int  z = x + y;  
x = -65; 
y = -120; 
int z1 = x + y; //test overflow

//printf("c = %u, f = %u, j = %u z = %llu, z1 = %llu\n",c , f, j, z, z1); 

return 0; 

}


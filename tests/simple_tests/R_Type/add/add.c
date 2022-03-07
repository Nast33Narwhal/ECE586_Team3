#include <stdio.h>
#include <stdint.h>

int main(){

//ADD tests
//Test Upper and Lower register values
int32_t a = 0x7FFFFFFF;
int32_t b = 0x80000001;
int32_t c = a + b;  // expected value of 0

/*
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
*/

//printf("b = %u, f = %u, j = %u z = %llu, z1 = %llu\n", b, f, j, z, z1); 

return 0; 

}


#include <stdio.h>

int main(){

//ADD tests

unsigned int a = 5; 
unsigned int b = 6; 
unsigned int c = a + b;  //0xb

unsigned int d = -5; 
unsigned int e = 6; 
unsigned int f = d + e; //0x1

unsigned int h = -10; 
unsigned int i = -10; 
unsigned int j = h + i; //0xffffffec

unsigned long long int x = 0xF000; 
unsigned long long int y = 0xFFFFFFFFF; 
unsigned long long int z = x + y;  //100000efff
x = -65;     
y = -120; 
unsigned long long int z1 = x + y; //ffffffffffffff47

//printf("c = %u, f = %u, j = %u z = %llu, z1 = %llu\n",c , f, j, z, z1); 

}

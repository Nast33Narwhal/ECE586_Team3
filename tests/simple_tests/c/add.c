#include <stdio.h>

int main(){

//ADD tests

int32_t a = 5; 
int32_t b = 6; 
int32_t c = a + b;  //0xb

int32_t d = -5; 
int32_t e = 6; 
int32_t f = d + e; //0x1

int32_t h = -10; 
int32_t i = -10; 
int32_t j = h + i; //0xffffffec

int64_t x = 0xF000; 
int64_t y = 0xFFFFFFFFF; 
int64_t z = x + y;  //100000efff
x = -65; 
y = -120; 
int64_t z1 = x + y; //ffffffffffffff47

//printf("c = %u, f = %u, j = %u z = %llu, z1 = %llu\n",c , f, j, z, z1); 

}
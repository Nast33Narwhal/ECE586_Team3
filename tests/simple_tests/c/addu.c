#include <stdio.h>

int main(){

//ADD tests

u_int32_t a = 5; 
u_int32_t b = 6; 
u_int32_t c = a + b;  //0xb

u_int32_t d = -5; 
u_int32_t e = 6; 
u_int32_t f = d + e; //0x1

u_int32_t h = -10; 
u_int32_t i = -10; 
u_int32_t j = h + i; //0xffffffec

u_int64_t x = 0xF000; 
u_int64_t y = 0xFFFFFFFFF; 
u_int64_t z = x + y;  //100000efff
x = -65; 
y = -120; 
u_int64_t z1 = x + y; //ffffffffffffff47

//printf("c = %u, f = %u, j = %u z = %llu, z1 = %llu\n",c , f, j, z, z1); 

}
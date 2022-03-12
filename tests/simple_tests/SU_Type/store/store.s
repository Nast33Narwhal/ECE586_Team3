# Store Byte (SB)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0xF11
ORI x7, x7, 0x700
SB  x6, 0(x7)        # mem[0x00000700] should contain 0x00000011
SB  zero, 0(x7)
SB  x6, 1(x7)        # mem[0x00000700] should contain 0x00001100
SB  zero, 1(x7)
SB  x6, 2(x7)        # mem[0x00000700] should contain 0x00110000
SB  zero, 2(x7)
SB  x6, 3(x7)        # mem[0x00000700] should contain 0x11000000

# Store Half Word (SH)
AND x6, x6, zero
AND x7, x7, zero
LUI x6, 0xFFFF2
ORI x6, x6, 0x222
ORI x7, x7, 0x704
SH  x6, 0(x7)       # mem[0x00000704-8] should contain 0x00000000_00002222
SH  zero, 0(x7)
SH  x6, 1(x7)       # mem[0x00000704-8] should contain 0x00000000_00222200
SH  zero, 1(x7)
SH  x6, 2(x7)       # mem[0x00000704-8] should contain 0x00000000_22220000
SH  zero, 2(x7)
SH  x6, 3(x7)       # mem[0x00000704-8] should contain 0x00000022_22000000

# Store Word (SW)
AND x6, x6, zero
AND x7, x7, zero
LUI x6, 0x33333
ORI x6, x6, 0x333
ORI x7, x7, 0x710
SW  x6, 0(x7)       # mem[0x00000710-4] should contain 0x00000000_33333333
SW  zero, 0(x7)
SW  x6, 1(x7)       # mem[0x00000710-1] should contain 0x00000033_33333300
SW  zero, 1(x7)
SW  x6, 2(x7)       # mem[0x00000710-4] should contain 0x00003333_33330000
SW  zero, 2(x7)
SW  x6, 3(x7)       # mem[0x00000710-4] should contain 0x00333333_33000000

JR x1

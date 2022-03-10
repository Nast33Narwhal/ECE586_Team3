# Load Byte (LB)
# store word 0x11223344 at memory location 0x00000040, then load in each byte separately (11 -> 22 -> 33 -> 44)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x740
LUI x7, 0x11223
ORI x7, x7, 0x344
SW x7, 0(x6)
LB x5, 3(x6)
LB x5, 2(x6)
LB x5, 1(x6)
LB x5, 0(x6)

# LH / LW
# store another word 0x55667788 at memory location 0x00000044 if LH and LW correctly cross over memory locations divisible by 4
AND x7, x7, zero
LUI x7, 0x55667
ORI x7, x7, 0x788
SW x7, 4(x6)
LH x5, 0(x6)
LH x5, 1(x6)
LH x5, 2(x6)
LH x5, 3(x6)
LW x5, 0(x6)
LW x5, 1(x6)
LW x5, 2(x6)
LW x5, 3(x6)

#LHU / LBU
ORI x5, x5, 0x7FF
LBU x5, 0(x6)
ORI x5, x5, 0x7FF
LHU x5, 0(x6)

JR x1

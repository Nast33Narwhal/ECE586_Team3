# Load Byte (LB)
# store word 0x11223344 at memory location 0x00000040, then load in each byte separately (11 -> 22 -> 33 -> 44)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x740
LUI x7, 0x11223
ORI x7, x7, 0x344
SW x7, 0(x6)            
LB x5, 3(x6)        # should be 0x00000011
LB x5, 2(x6)        # should be 0x00000022
LB x5, 1(x6)        # should be 0x00000033
LB x5, 0(x6)        # should be 0x00000044

# LH / LW
# store another word 0x55667788 at memory location 0x00000044 if LH and LW correctly cross over memory locations divisible by 4
AND x7, x7, zero
LUI x7, 0x55667
ORI x7, x7, 0x788
SW x7, 4(x6)        
LB x5, 4(x6)        # should be 0xFFFFFF88 (sign extension test for LB)
LH x5, 0(x6)        # should be 0x00003344
LH x5, 1(x6)        # should be 0x00002233
LH x5, 2(x6)        # should be 0x00001122
LH x5, 3(x6)        # should be 0xFFFF8811 (sign extension)
LW x5, 0(x6)        # should be 0x11223344
LW x5, 1(x6)        # should be 0x88112233
LW x5, 2(x6)        # should be 0x77881122
LW x5, 3(x6)        # should be 0x66778811

#LHU / LBU
ORI x5, x5, 0xFFF   
LBU x5, 0(x6)       # should be 0x44000000
ORI x5, x5, 0xFFF
LHU x5, 0(x6)       # should be 0x33440000

JR x1

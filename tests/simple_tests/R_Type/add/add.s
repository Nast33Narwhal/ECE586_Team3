# largest positive number + largest negative number
ORI x6, x6, 0xFFF
SRLI x6, x6, 0x1
LUI x7, 0x80000
ADD x5, x6, x7

# negative number result (1 + (-9) = -8)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x001
ORI x7, x7, 0xFF7
ADD x5, x6, x7

# postive number result (5 + (-1) = 4)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x005
ORI x7, x7, 0xFFF
ADD x5, x6, x7

# negative saturation (negative bound + negative bound)
AND x6, x6, zero
AND x7, x7, zero
LUI x6, 0x80000
LUI x7, 0x80000
ADD x5, x6, x7

# positive saturation (positive bound + positive bound)
AND x6, x6, zero
AND x7, x7, zero   
ORI x6, x6, 0xFFF
SRLI x6, x6, 0x1
ORI x7, x7, 0xFFF
SRLI x7, x7, 0x1
ADD x5, x6, x7


# largest positive number + largest negative number
ORI x6, x6, 0xFFF
SRLI x6, x6, 0x1
LUI x7, 0x80000
ADD x5, x6, x7          # x5 should be -1 (0x7FFFFFFF + 0x80000000 = 0xFFFFFFFF = -1 (signed))

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

# negative overflow (negative bound + negative bound)
AND x6, x6, zero
AND x7, x7, zero
LUI x6, 0x80000
LUI x7, 0x80000
ADD x5, x6, x7          # result should be 0 (0x80000000 + 0x80000000 = 0x(1)00000000 (1 ignored))
ORI x7, x7, 0xFFB
ADD x5, x6, x7          # result should be 0x7FFFFFFB (0x80000000 + 0xFFFFFFFB = 0x(1)7FFFFFFB

# positive overflow (positive bound + positive bound)
AND x6, x6, zero
AND x7, x7, zero   
ORI x6, x6, 0xFFF
SRLI x6, x6, 0x1
ORI x7, x7, 0xFFF
SRLI x7, x7, 0x1
ADD x5, x6, x7          # result should be -2 (0x7FFFFFFF + 0x7FFFFFFF = 0xFFFFFFFE)
AND x7, x7, zero
ORI x7, x7, 0x005       
ADD x5, x6, x7          # results should be 0x80000004 (0x7FFFFFFF + 0x00000005 = 0x80000004)

JR x1

# positive - negative (1 - (-9) = 10)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x001
ORI x7, x7, 0xFF7
SUB x5, x6, x7

# negative - negative (-1 - (-9) = 8)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0xFFF
ORI x7, x7, 0xFF7
SUB x5, x6, x7

# negative saturation (largest negative - largest positive
AND x6, x6, zero
AND x7, x7, zero
LUI x6, 0x80000
ORI x6, x6, 0x000
ORI x7, x7, 0xFFF
SRLI x7, x7, 0x1
SUB x5, x6, x7

# positive saturation (largest positive - largest negative
AND x6, x6, zero
AND x7, x7, zero
LUI x6, 0x80000
ORI x6, x6, 0x000
ORI x7, x7, 0xFFF
SRLI x7, x7, 0x1
SUB x5, x7, x6

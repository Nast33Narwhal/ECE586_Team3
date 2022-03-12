# ADDI
# Positive overflow test (largest number + immediate)
ORI x6, x6, 0xFFF
SRLI x6, x6, 0x1
ADDI x5, x6, 0x7FF          # x5 should be (0x7FFFFFFF + 0x000007FF = 0x800007FE)

# Negative overflow test (Largest negative number + -immediate)
AND x6, x6, zero
LUI x6, 0x80000
ADDI x5, x6, 0x800          # x5 should be (0x80000000 + 0xFFFFF800 = 0x(1)7FFFF800

# Negative result test
AND x6, x6, zero
ORI x6, x6, 0x001
ADDI x5, x6, 0xFFB          # x5 should be -4 (1 + -5 = -4)

# Positive result test
AND x6, x6, zero
ORI x6, x6, 0xFFF
ADDI x5, x6, 0x005          # x5 should be 4 (-1 + 5 = 4)

# MV pseudoinstruction test
AND x6, x6, zero
LUI x6, 0xF0F0F
ORI x6, x6, 0x0F0
ADDI x5, x6, 0x000          # x5 should be 0xF0F0F0F0 (same as x6)

JR x1


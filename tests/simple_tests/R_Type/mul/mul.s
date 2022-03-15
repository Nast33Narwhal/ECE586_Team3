# Multiply
addi x5, x0, 5
addi x6, x0, 6
mul x10, x5, x6 #0x0000001E = 30
addi x7, x0, -6 #0xFFFFFFFA = -6
mul x11, x5, x7 #0XFFFFFFE2 = -30

# Multiply High
mulh x12, x5, x6 #5*6 = 0x00000000_0000001E
mulh x13, x5, x7 #5*-6= 0x5 * 0xFFFFFFFA = 0xFFFFFFFF_FFFFFFE2, store 0xFFFFFFFF

# Multiply High Unsigned
mulhu x14, x5, x6 #5*6 = 0x5 * 0x6 = 0x00000000_0000001E = 0x0
mulhu x15, x5, x7 #5*-6 = 0x5 * 0xFFFFFFFA = 0x00000004_FFFFFFE2, store 0x00000004

# Multiply High Signed Unsigned
mulhsu x16, x7, x5 #0xFFFFFFFA * 0x5 = 0xFFFFFFFF
mulhsu x17, x5, x6 #0x5 * 0x6 = 0x00000000_0000001E, store 0x00000000

# Divide
div x18, x10, x5 # 30/5=6 = 0x00000006
div x19, x10, x7 # 30/-6 = -5 = 0xFFFFFFFB

# Divide Unsigned
divu x20, x7, x5 #0xFFFFFFFA / 0x5 = 0x33333332 

# Remainder
rem x21, x10, x5 #30%5 = 6r0 = 0
rem x22, x6, x5 #6%5 = 1r1 = 1


# Remainder Unsigned
remu x23, x7, x6 #0xFFFFFFFA % 0x6 = r4 = 4

# Divide by 0 Checks, per Table 7.1
divu x24, x5, x0 #5 / 0 = 2^32 - 1 = 4294967295 or signed = -1
remu x25, x5, x0 #5 % 0 = 5
div x26, x5, x0 #5 / 0 = -1
rem x27, x6, x0 #6 % 0 = 6

# Overflow Checks, per Table 7.1
lui x28, 524288 #0x80000 becomes 0x80000000 = -(2^31), max negative number
addi x29, x0, -1 #0xFFFFFFFF
div x30, x28, x29 #-2147483648 / -1 =-2147483648
rem x31, x28, x29 #-2147483648 % -1 = 0


jr ra

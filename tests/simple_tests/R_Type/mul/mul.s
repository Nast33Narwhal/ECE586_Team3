# Multiply
addi x5, x0, 5
addi x6, x0, 6
mul x10, x5, x6 #0x0000001E = 30
addi x6, x0, -6
mul x11, x5, x6 #0XFFFFFFE2 = -30

# Multiply High
mulh x12, x5, x6 #0xFFFFFFFF_FFFFFFE2, store 0xFFFFFFFF

# Multiply High Unsigned
mulhu x13, x5, x6 #0x00000004_FFFFFFE2, store 0x00000004

# Multiply High Signed Unsigned
mulhsu x14, x5, x6 #0x00000000_0000001E, store 0x00000000

# Divide
div x15, x10, x5 #30/5=6 = 0x00000006

# Divide Unsigned
divu x16, x10, x6 #30/-6= 5 unsigned div 

# Remainder
rem x17, x10, x5 #30%5 = 6r0 = 0
rem x18, x6, x5 #6%5 = 1r1 = 1

# Remainder Unsigned
rem x19, x6, x5 #6%5 = 1r1 = 1

jr ra

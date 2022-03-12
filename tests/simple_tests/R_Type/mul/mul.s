# Multiply
addi x5, x0, 5
addi x6, x0, 6
mul x10, x5, x6
addi x6, x0, -6
mul x11, x5, x6

# Multiply High
mulh x12, x5, x6

# Multiply High Unsigned
mulhu x13, x5, x6

# Multiply High Signed Unsigned
mulhsu x14, x5, x6

# Divide
div x15, x12, x5

# Divide Unsigned
divu x16, x12, x5

# Remainder
rem x17, x12, x5
rem x18, x6, x5

# Remainder Unsigned
rem x19, x6, x5

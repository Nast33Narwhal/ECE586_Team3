# Test all Instructions
# R type
ADD  x3, x4, x5
SUB  x3, x4, x5
SLL  x6, x7, x8
SLT  x3, x4, x5
SLTU x3, x4, x5
XOR  x3, x4, x5
SRL  x3, x4, x5
SRA  x6, x7, x8
OR   x3, x4, x5
AND  x3, x4, x5
# I type
ADDI  x9, x0, 120 # base mem address for loads and stores
LB    x3, 3(x9)
LH    x3, 2(x9)
LW    x6, 0(x9)
LBU   x3, 3(x9)
LHU   x3, 2(x9)
ADDI  x3, x4, 8
SLLI  x3, x4, 1
SLTI  x3, x4, 2
SLTIU x3, x4, 3
XORI  x3, x4, 4
SRLI  x3, x4, 5
SRAI  x3, x4, 6
ORI   x3, x4, 7
ANDI  x3, x4, 8
JALR  x2, x4
# S type
SB    x3, 3(x9)
SH    x3, 2(x9)
SW    x3, 0(x9)
# U type
AUIPC x3, 123
LUI   x3, 124
# B type
BEQ   x3, x4, T1
BNE   x3, x4, T2
BLT   x3, x4, T3
BGE   x3, x4, T4
BLTU  x3, x4, T5
BGEU  x3, x4, T6
T1:
T2:
T3:
T4:
T5:
T6:
JAL   x3, T7
T7:

JR ra

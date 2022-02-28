# Test all Instructions
# R type
ADD  x3, x4, x5
SUB  x3, x4, x5
SLL  x3, x4, x5
SLT  x3, x4, x5
SLTU x3, x4, x5
XOR  x3, x4, x5
SRL  x3, x4, x5
SRA  x3, x4, x5
OR   x3, x4, x5
AND  x3, x4, x5
# I type
LB    x3, 3(x4)
LH    x3, 2(x4)
LW    x3, 0(x4)
LBU   x3, 3(x4)
LHU   x3, 2(x4)
ADDI  x3, x4, 1
SLLI  x3, x4, 1
SLTI  x3, x4, 1
SLTIU x3, x4, 1
XORI  x3, x4, 1
SRLI  x3, x4, 1
SRAI  x3, x4, 1
ORI   x3, x4, 1
ANDI  x3, x4, 1
JALR  x2, x4
# S type
SB    x3, 3(x4)
SH    x3, 2(x4)
SW    x3, 0(x4)
# U type
AUIPC x3, 123
LUI   x3, 123
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

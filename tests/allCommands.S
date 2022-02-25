addi x3, x0, 12
SLTI x4, x0, -15
SLTIU x5, x3, 12
ANDI x6, x4, 15
ORI x7, x4, 12
XORI x8, x4, 12
SLLI x3, x3, 2
SRLI x3, x3, 1
SRAI x3, x3, 1
LUI x9, 1233
AUIPC x10, 16
ADD x11, x3, x4
SLT x4, x0, x5
SLTU x4, x0, x5
AND x4, x4, x5
OR x6, x4, x5
XOR x5, x4, x6
SLL x6, x4, x5
SRL x6, x5, x4
SRA x6, x4, x5
SUB x7, x8, x5


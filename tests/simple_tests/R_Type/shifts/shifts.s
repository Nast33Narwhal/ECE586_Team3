# SLL
ORI x6, x6, 0xFFF
ORI x7, x7, 0x010
SLL x5, x6, x7
SLL x5, x5, x7

#SRL
AND x5, x5, zero
SRL x5, x6, x7
SRL x5, x5, x7

#SRA
AND x5, x5, zero
LUI x6, 0x80000
SRA x5, x6, x7
AND x5, x5, zero
LUI x6, 0x40000
SRA x5, x6, x7

# SLL
ORI x6, x6, 0xFFF
ORI x7, x7, 0x010
SLL x5, x6, x7          # x5 should be 0xFFFF0000 (0xFFFFFFFF shifted left by 16 bits)
SLL x5, x5, x7          # x5 should be 0x00000000

#SRL
AND x5, x5, zero
SRL x5, x6, x7          # x5 should be 0x0000FFFF (0xFFFFFFFF shifted right by 16 bits)
SRL x5, x5, x7          # x5 should be 0x00000000

#SRA
AND x5, x5, zero        
LUI x6, 0x80000         
SRA x5, x6, x7          # x5 should be 0xFFFF8000
AND x5, x5, zero
LUI x6, 0x40000         # x5 should be 0x00004000
SRA x5, x6, x7

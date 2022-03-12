# LUI (Doesn't really need to be tested because it has been tested implicitly in other function tests)
ORI x6, x6, 0x7FF           # initially set x6 to 0xFFFFFFFF
LUI x6, 0xFFFFF         # test setting x6 to 0xFFFFF000
LUI x6, 0x00000         # test setting x6 to 0x00000000

# AUIPC
AUIPC x5, 0x11111       # from testing, PC here should be 0x0000000c, so x5 should be 0x1111100c

JR x1

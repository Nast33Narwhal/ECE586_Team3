# ANDI
# Test sign-extension and functionality
ORI x6, x6, 0xFFF
ANDI x5, x6, 0xFFF          # result should be 0xFFFFFFFF
ANDI x5, x6, 0x000          # result should be 0x00000000

# ORI
# Test sign-extension and functionality
ORI x5, x5, 0x000           # result should be 0x00000000
ORI x5, x5, 0xFFF           # result should be 0xFFFFFFFF

# XORI
# Test sing-extension and functionality
LUI x6, 0x55555
ORI x6, x6, 0x555
XORI x5, x6, 0xFFF          # result should be 0xAAAAAAAA
XORI x5, x6, 0x000          # result should be 0x55555555    
JR x1

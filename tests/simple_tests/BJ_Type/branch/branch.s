# BEQ
AND x6, x6, zero
AND x7, x7, zero
ORI x7, x7, 0x001
BEQ x6, zero, 0x100     # should increment the PC by 0x200 (0x100 << 1 because 2 byte aligned)]
BEQ x6, zero, 0x79C     # should decrement PC by 0x200
BEQ x6, x7, 0x100       # should do nothing, PC + 4

# BNE
BNE x6, zero, 0x100     # should do nothing, PC + 4
BNE x6, x7, 0x100       # should increment PC by 0x200
BNE x6, x7, 0x79C       # should decrement PC by 0x200

# BLT
BLT x6, zero, 0x100     # should do nothing
BLT x6, x7, 0x100       # should increment PC by 0x200
BLT x6, x7, 0x79C       # should decrement PC by 0x200

# BGE
BGE x6, zero, 0x100     # should increment PC by 0x200
BGE x7, x6, 0x79C       # should decrement PC by 0x200
BGE x6, x7, 0x100       # should do nothing

# BLTU
BLTU x6, zero, 0x100    # should do nothing
BLTU x6, x7, 0x700      # should increment PC by 0x1000
BLTU x6, x7, 0x700      # should decrement PC by 0x1000

# BGEU
BGEU x6, zero, 0x700    # should increment PC by 0x1000
BGEU x7, x6, 0x700      # should decrement PC by 0x1000
BGEU x6, x7, 0x100      # should do nothing

JR x1

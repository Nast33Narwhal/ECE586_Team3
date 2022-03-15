    # BEQ
    AND x6, x6, zero
    AND x7, x7, zero
    ORI x7, x7, 0x001
    BEQ x6, zero, .L1       # jump to .L1
.L1:
    BEQ x6, zero, .L2       # jump to .L2
.L2:
    BEQ x6, x7, .L3         # should do nothing, PC + 4

    # BNE
    BNE x6, zero, .L3       # should do nothing, PC + 4
    BNE x6, x7, .L3         # jump to .L3
.L3:
    BNE x6, x7, .L4         # jump to .L4
.L4:

    # BLT
    BLT x6, zero, .L5       # should do nothing
    BLT x6, x7, .L5         # jump to .L5
.L5:
    BLT x6, x7, .L6         # jump to .L6
.L6:

    # BGE
    BGE x6, zero, .L7       # jump to .L7
.L7:
    BGE x7, x6, .L8         # jump to .L8
.L8:
    BGE x6, x7, .L9         # should do nothing

    # BLTU
    BLTU x6, zero, .L9      # should do nothing
    BLTU x6, x7, .L9        # jump to .L9
.L9:
    BLTU x6, x7, .L10       # jump to .L10
.L10:

    # BGEU
    BGEU x6, zero, .L11     # jump to .L11
.L11:
    BGEU x7, x6, .L12       # jump to .L12
.L12:
    BGEU x6, x7, .L13       # should do nothing
.L13:
    JR x1

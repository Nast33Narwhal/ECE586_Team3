# SLLI
ORI x6, x6, 0xFFF
SLLI x5, x6, 0x01F      # result should be 0x80000000
SLLI x5, x6, 0x010      # result should be 0xFFFF0000
SLLI x5, x6, 0x000      # result should be 0xFFFFFFFF

# SLRI
SRLI x5, x6, 0x01F      # result should be 0x00000001
SRLI x5, x6, 0x010      # result should be 0x0000FFFF
SRLI x5, x6, 0x000      # result should be 0xFFFFFFFF

# SRAI
AND x6, x6, zero
LUI x6, 0x80000
SRAI x5, x6, 0x000      # result should be 0x80000000
SRAI x5, x6, 0x010      # result should be 0xFFFF8000
SRAI x5, x6, 0x01F      # result should be 0xFFFFFFFF
JR x1

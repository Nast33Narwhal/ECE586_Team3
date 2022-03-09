ORI x6, x6, 0x7FF
SRLI x6, x6, 0x1
LUI x7, 0x80000
ORI x7, x7, 0x001
ADD x5, x6, x7

AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x001
ORI x7, x7, 0x7F7
ADD x5, x6, x7

AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x005
ORI x7, x7, 0x7FF
ADD x5, x6, x7

AND x6, x6, zero
AND x7, x7, zero
LUI x6, 0x80000
ORI x6, x6, 0x001
LUI x7, 0x80000
ORI x7, x7, 0x001
ADD x5, x6, x7

AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x7FF
SRLI x6, x6, 0x1
ORI x7, x7, 0x7FF
SRLI x7, x7, 0x1
ADD x5, x6, x7


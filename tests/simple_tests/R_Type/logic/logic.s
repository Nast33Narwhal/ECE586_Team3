# AND
LUI x7, 0xF0F0F
ORI x7, x7, 0x0F0
ORI x6, x6, 0x7FF
AND x5, x6, x7      # should be value of x7
AND x5, x5, zero    # should be all zeros

# OR
OR x5, x6, x7       # should be all 1s
OR x5, x7, zero     # should be value of x7
AND x5, x5, zero

# XOR
XOR x5, x6, x7      # should be oposite of x7

# AND
LUI x7, 0xF0F0F
ORI x7, x7, 0x0F0
ORI x6, x6, 0xFFF
AND x5, x6, x7      # x5 should be 0xF0F0F0F0
AND x5, x5, zero    # x5 should be 0x00000000

# OR
OR x5, x6, x7       # x5 should be 0xFFFFFFFF
OR x5, x7, zero     # x5 should be 0xF0F0F0F0
AND x5, x5, zero

# XOR
XOR x5, x6, x7      # x5 should be oposite of x7: 0x0F0F0F0F

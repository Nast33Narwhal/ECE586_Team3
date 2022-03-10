# SLT
# comparing negatives
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x7FB       # x6 = -5
ORI x7, x7, 0x7FC       # x7 = -4
SLT x5, x6, x7          # x5 should be 1, -5 < -4

# comparing positives
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x005       # x6 = 5
ORI x7, x7, 0x004       # x7 = 4
SLT x5, x6, x7          # x5 should be 0, 5 !< 4

# positive/negative comparison
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x7FF       # x6 = -1
ORI x7, x7, 0x001       # x7 = 1
SLT x5, x6, x7          # x5 should be 1, -1 < 1

# equality test (rs1 == rs2)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x001
ORI x7, x7, 0x001
SLT x5, x6, x7          # x5 should be 0, 1 !< 1

# SLTU
# comparing numbers with 1 in MSBit
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x7FE       
ORI x7, x7, 0x7FF
SLTU x5, x6, x7         # x5 should be 1, 0xFFFFFFFE < 0xFFFFFFFF

# comparing numbers with 0 in MSBit
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x002
ORI x7, x7, 0x001
SLTU x5, x6, x7         # x5 should be 0, 2 !< 1

# equality test (rs1 == rs2)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x001
ORI x7, x7, 0x001
SLTU x5, x6, x7         # x5 should be 0, 1 !< 1

# special case test: SLTU rd, zero, rs2 (sets rd to 1 is rs2 != 0)
AND x6, x6, zero
AND x7, x7, zero
ORI x6, x6, 0x001
ORI x7, x7, 0x000
SLTU x5, zero, x6       # x5 should be 1, 1 != 0
SLTU x5, zero, x7       # x5 should be 0, 0 == 0

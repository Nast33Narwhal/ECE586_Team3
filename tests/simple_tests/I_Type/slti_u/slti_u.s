# SLTI
# testing with negative immediate
ORI x6, x6, 0x005
SLTI x5, x6, 0xFFF          # x5 should be 0 (5 !< -1)

# testing with positive immediate
SLTI x5, x6, 0x006          # x5 should be 1 (5 < 6)

# SLTIU
# testing for sign extension that is not negative
SLTIU x5, x6, 0xFFF          # x5 should be 1 (5 < 0xFFFFFFFF)

# testing with positive immediate for 0 result
SLTIU x5, x6, 0x004          # x5 should be 0 (5 !< 4)

# check for pseudo instruction case: SEQZ
AND x6, x6, zero
SLTIU x5, x6, 0x1            # result should be 1 because x6 == 0
ORI x6, x6, 0x001
SLTIU x5, x6, 0x1            # result should be 0 because x6 != 0 && x6 !< 1

JR x1

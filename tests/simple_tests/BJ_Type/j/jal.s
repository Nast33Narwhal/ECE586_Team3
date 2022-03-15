addi x10, x0, 12
addi x11, x0, 17
jal x12, ADD2NUMBERS
addi x15, x0, 27
jal x13, SUB2NUMBERS
jr ra
ADD2NUMBERS:
add x14, x10, x11
jr x12
SUB2NUMBERS:
sub x12, x14, x10
jr x13

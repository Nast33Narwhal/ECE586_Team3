
# ecall test case 

LUI t0, 0x52495  # first part of word in hex
ORI t1, x0, 0x343
OR t0, t0, t1 # load in second part to get RISC! or 0x68657921
SW t0, -32(sp) # store word 
ADD a1, sp, -32 # load address of word in a1
ADDI a0, x0, 1 # specifies STDOUT
ADDI a2, x0, 4 # length of string hey!
ADDI a7, x0, 64 # system call for printing 
ecall       # should print HEY! to STDOUT

ADDI a1, sp, -128 # decrement stack to specify address of buffer
ADDI a0, x0, 0 # specifies STDIN
ADDI a2, x0, 20 # specifies length of input string
ADDI a7, x0, 63 # system call for reading 
ecall

ADDI a7, x0, 94 # should exit program
ecall 

jr ra

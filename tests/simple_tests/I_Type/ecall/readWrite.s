.equ STDIN, 0
.equ STDOUT, 1
.equ SYS_READ, 63
.equ MAX_CHARS, 255
.equ SYS_EXIT, 94
.equ SYS_WRITE, 64

.section .bss
.align 2

buffer: .space 256

.section .rodata
.align 2

msg: .ascii "I like tacos!\0"
l_msg: .byte .-msg

.section .text
.align 2

# read from stdin into buffer
li a0, STDIN
la a1, buffer
li a2, MAX_CHARS
li a7, SYS_READ
ecall

# write buffer
li a0, STDOUT
la a1, buffer
li a2, MAX_CHARS
li a7, SYS_WRITE
ecall

# write I like Tacos!
li a0, STDOUT
la a1, msg
lbu a2, l_msg
li a7, SYS_WRITE
ecall

# exit
li a0, 0
li a7, SYS_EXIT
ecall


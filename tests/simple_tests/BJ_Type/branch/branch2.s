	.file	"branch2.c"
	.option pic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,3
	sw	a5,-20(s0)
	j	.L2
.L8:
	sw	zero,-24(s0)
	j	.L3
.L7:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	ble	a4,a5,.L4
#APP
# 15 "branch2.c" 1
	addi t4, x0, 1
# 0 "" 2
# 16 "branch2.c" 1
	addi t5, x0, 0
# 0 "" 2
# 17 "branch2.c" 1
	addi t6, x0, 0
# 0 "" 2
#NO_APP
	j	.L5
.L4:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	bne	a4,a5,.L6
#APP
# 23 "branch2.c" 1
	addi t4, x0, 0
# 0 "" 2
# 24 "branch2.c" 1
	addi t5, x0, 1
# 0 "" 2
# 25 "branch2.c" 1
	addi t6, x0, 0
# 0 "" 2
#NO_APP
	j	.L5
.L6:
#APP
# 31 "branch2.c" 1
	addi t4, x0, 0
# 0 "" 2
# 32 "branch2.c" 1
	addi t5, x0, 0
# 0 "" 2
# 33 "branch2.c" 1
	addi t6, x0, 1
# 0 "" 2
#NO_APP
.L5:
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L3:
	lw	a4,-24(s0)
	li	a5,6
	ble	a4,a5,.L7
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-20(s0)
	li	a5,6
	ble	a4,a5,.L8
	li	a5,0
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits

	.file	"branch2.c"
	.option pic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	li	a5,3
	sw	a5,-20(s0)
	j	.L2
.L9:
	sw	zero,-24(s0)
	j	.L3
.L8:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	ble	a4,a5,.L4
	call	branch_greater@plt
	j	.L5
.L4:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	bne	a4,a5,.L6
	call	branch_equal@plt
	j	.L5
.L6:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	bge	a4,a5,.L11
	call	branch_less@plt
	j	.L5
.L11:
	nop
.L5:
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L3:
	lw	a4,-24(s0)
	li	a5,6
	ble	a4,a5,.L8
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-20(s0)
	li	a5,6
	ble	a4,a5,.L9
	li	a5,0
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.align	2
	.globl	branch_greater
	.type	branch_greater, @function
branch_greater:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,1
	sw	a5,-20(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	branch_greater, .-branch_greater
	.align	2
	.globl	branch_equal
	.type	branch_equal, @function
branch_equal:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,2
	sw	a5,-20(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	branch_equal, .-branch_equal
	.align	2
	.globl	branch_less
	.type	branch_less, @function
branch_less:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,3
	sw	a5,-20(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	branch_less, .-branch_less
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits

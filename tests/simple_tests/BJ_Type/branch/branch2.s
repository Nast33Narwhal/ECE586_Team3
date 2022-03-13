	.file	"branch2.c"
	.option pic
	.text
	.globl	global
	.bss
	.align	2
	.type	global, @object
	.size	global, 4
global:
	.zero	4
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	li	a5,-6
	sw	a5,-20(s0)
	j	.L2
.L8:
	sw	zero,-32(s0)
	j	.L3
.L7:
	lw	a4,-20(s0)
	lw	a5,-32(s0)
	ble	a4,a5,.L4
	call	branch_greater@plt
	j	.L5
.L4:
	lw	a4,-20(s0)
	lw	a5,-32(s0)
	bne	a4,a5,.L6
	call	branch_equal@plt
	j	.L5
.L6:
	lw	a4,-20(s0)
	lw	a5,-32(s0)
	bge	a4,a5,.L5
	call	branch_less@plt
.L5:
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L3:
	lw	a4,-32(s0)
	li	a5,6
	ble	a4,a5,.L7
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-20(s0)
	li	a5,6
	ble	a4,a5,.L8
	li	a5,-6
	sw	a5,-24(s0)
	j	.L9
.L15:
	sw	zero,-28(s0)
	j	.L10
.L14:
	lw	a5,-28(s0)
	lw	a4,-24(s0)
	bleu	a4,a5,.L11
	call	branch_greater@plt
	j	.L12
.L11:
	lw	a5,-28(s0)
	lw	a4,-24(s0)
	bne	a4,a5,.L13
	call	branch_equal@plt
	j	.L12
.L13:
	lw	a5,-28(s0)
	lw	a4,-24(s0)
	bgeu	a4,a5,.L12
	call	branch_less@plt
.L12:
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L10:
	lw	a4,-28(s0)
	li	a5,6
	ble	a4,a5,.L14
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L9:
	lw	a4,-24(s0)
	li	a5,6
	bleu	a4,a5,.L15
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
	addi	sp,sp,-16
	sw	s0,12(sp)
	addi	s0,sp,16
	la	a5,global
	li	a4,1
	sw	a4,0(a5)
	nop
	lw	s0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	branch_greater, .-branch_greater
	.align	2
	.globl	branch_equal
	.type	branch_equal, @function
branch_equal:
	addi	sp,sp,-16
	sw	s0,12(sp)
	addi	s0,sp,16
	la	a5,global
	li	a4,2
	sw	a4,0(a5)
	nop
	lw	s0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	branch_equal, .-branch_equal
	.align	2
	.globl	branch_less
	.type	branch_less, @function
branch_less:
	addi	sp,sp,-16
	sw	s0,12(sp)
	addi	s0,sp,16
	la	a5,global
	li	a4,3
	sw	a4,0(a5)
	nop
	lw	s0,12(sp)
	addi	sp,sp,16
	jr	ra
	.size	branch_less, .-branch_less
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits

	.section .text.init
	.extern start
	
	.global init
init:
	la sp, stack_end
	call start

dead:	wfi
	j dead

	.section .text
	.global sbi_putchar
sbi_putchar:
	li a6, 0
	li a7, 1
ecall:
	ecall
	ret

	.global sbi_shutdown
sbi_shutdown:
	li a6, 0
	li a7, 8
	j ecall
	
	.bss
	.align 12
stack:
	.fill 4096
stack_end:

	.file	"p1.c"
	.text

## FIXED_INIT

	.section	.rodata
        .globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4


.LC0:
	.string	"%d\n"
	.text

## TAC_BEGINFUN

	.globl	main
	.type	main, @function
main:
.LFB0:

	pushq	%rbp
	movq	%rsp, %rbp
	movl	$5, %esi

## TAC_PRINT

	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_ENDFUN

	popq	%rbp
	ret
	
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

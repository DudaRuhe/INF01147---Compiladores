	.file	"t1.c"
	.text
	.section	.rodata
.LC0:
	.string	"teste"
	.text
	
## TAC_BEGINFUN

	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_PRINT	

	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_ENDFUN	

	popq	%rbp
	ret

## DATA_SECTION

a:
	.long	6
	.section	.rodata



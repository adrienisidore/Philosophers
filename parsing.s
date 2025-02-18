	.file	"parsing.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"philo: Invalid argument(s), enter valid arguments between 1 and 2 147 483 647ms\n"
	.text
	.type	ft_checkint, @function
ft_checkint:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L2
.L3:
	addl	$1, -8(%rbp)
.L2:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	ft_ispace@PLT
	testl	%eax, %eax
	jne	.L3
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	ft_isnum@PLT
	testl	%eax, %eax
	jne	.L4
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$43, %al
	je	.L4
	leaq	.LC0(%rip), %rdi
	call	ft_error@PLT
.L4:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$43, %al
	jne	.L5
	addl	$1, -8(%rbp)
.L5:
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	addl	$1, -8(%rbp)
	addl	$1, -4(%rbp)
.L6:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	ft_isnum@PLT
	testl	%eax, %eax
	jne	.L7
	cmpl	$10, -4(%rbp)
	jle	.L9
	leaq	.LC0(%rip), %rdi
	call	ft_error@PLT
	jmp	.L9
.L10:
	addl	$1, -8(%rbp)
.L9:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	ft_ispace@PLT
	testl	%eax, %eax
	jne	.L10
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L11
	leaq	.LC0(%rip), %rdi
	call	ft_error@PLT
.L11:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ft_atol@PLT
	testq	%rax, %rax
	jne	.L13
	leaq	.LC0(%rip), %rdi
	call	ft_error@PLT
.L13:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	ft_checkint, .-ft_checkint
	.section	.rodata
	.align 8
.LC1:
	.string	"philo: Correct syntax: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
	.align 8
.LC2:
	.string	"philo: number_of_philosophers must be between 1 and 200\n"
	.text
	.globl	ft_parser
	.type	ft_parser, @function
ft_parser:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$5, -20(%rbp)
	je	.L15
	cmpl	$6, -20(%rbp)
	je	.L15
	leaq	.LC1(%rip), %rdi
	call	ft_error@PLT
.L15:
	movl	$0, -4(%rbp)
	jmp	.L16
.L17:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	ft_checkint
.L16:
	addl	$1, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L17
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	ft_atol@PLT
	testq	%rax, %rax
	jle	.L18
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	ft_atol@PLT
	cmpq	$200, %rax
	jle	.L20
.L18:
	leaq	.LC2(%rip), %rdi
	call	ft_error@PLT
.L20:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	ft_parser, .-ft_parser
	.ident	"GCC: (Ubuntu 10.5.0-1ubuntu1~22.04) 10.5.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:

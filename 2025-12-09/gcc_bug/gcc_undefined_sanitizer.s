	.file	"main.c"
	.text
	.data
	.align 2
	.type	.Lubsan_type0, @object
	.size	.Lubsan_type0, 10
.Lubsan_type0:
	.value	-1
	.value	0
	.string	"'int'"
	.section	.rodata
.LC0:
	.string	"main.c"
	.section	.data.rel.local,"aw"
	.align 32
	.type	.Lubsan_data1, @object
	.size	.Lubsan_data1, 32
.Lubsan_data1:
	.quad	.LC0
	.long	5
	.long	14
	.quad	.Lubsan_type0
	.byte	2
	.byte	1
	.zero	6
	.text
	.globl	set_42
	.type	set_42, @function
set_42:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	cmpq	$0, -8(%rbp)
	je	.L2
	movq	%rax, %rdx
	andl	$3, %edx
	testq	%rdx, %rdx
	je	.L3
.L2:
	movq	%rax, %rsi
	leaq	.Lubsan_data1(%rip), %rax
	movq	%rax, %rdi
	call	__ubsan_handle_type_mismatch_v1@PLT
.L3:
	movq	-8(%rbp), %rax
	movl	$42, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	set_42, .-set_42
	.section	.data.rel.local
	.align 32
	.type	.Lubsan_data2, @object
	.size	.Lubsan_data2, 32
.Lubsan_data2:
	.quad	.LC0
	.long	16
	.long	12
	.quad	.Lubsan_type0
	.byte	2
	.byte	0
	.zero	6
	.text
	.globl	set_number
	.type	set_number, @function
set_number:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	set_42
	movq	-8(%rbp), %rax
	cmpq	$0, -8(%rbp)
	je	.L5
	movq	%rax, %rdx
	andl	$3, %edx
	testq	%rdx, %rdx
	je	.L6
.L5:
	movq	%rax, %rsi
	leaq	.Lubsan_data2(%rip), %rax
	movq	%rax, %rdi
	call	__ubsan_handle_type_mismatch_v1@PLT
.L6:
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	set_number, .-set_number
	.section	.rodata
.LC1:
	.string	"value=%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	call	set_number
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.section	.data.rel.local
	.align 32
	.type	.Lubsan_data0, @object
	.size	.Lubsan_data0, 40
.Lubsan_data0:
	.quad	.LC0
	.long	21
	.long	5
	.quad	0
	.long	0
	.long	0
	.long	1
	.zero	4
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:

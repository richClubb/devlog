	.file	"main.c"
	.text
	.data
	.align 32
	.type	.Lubsan_type0, @object
	.size	.Lubsan_type0, 10
.Lubsan_type0:
	.value	-1
	.value	0
	.string	"'int'"
	.zero	54
	.section	.rodata
	.align 32
.LC0:
	.string	"main.c"
	.zero	57
	.section	.data.rel.local,"aw"
	.align 32
	.type	.Lubsan_data1, @object
	.size	.Lubsan_data1, 32
.Lubsan_data1:
	.quad	.LC0
	.long	6
	.long	14
	.quad	.Lubsan_type0
	.byte	2
	.byte	1
	.zero	6
	.zero	32
	.text
	.globl	set_42
	.type	set_42, @function
set_42:
.LASANPC6:
.LFB6:
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
	movq	%rax, %rdx
	shrq	$3, %rdx
	addq	$2147450880, %rdx
	movzbl	(%rdx), %edx
	testb	%dl, %dl
	setne	%sil
	movq	%rax, %rcx
	andl	$7, %ecx
	addl	$3, %ecx
	cmpb	%dl, %cl
	setge	%dl
	andl	%esi, %edx
	testb	%dl, %dl
	je	.L4
	movq	%rax, %rdi
	call	__asan_report_store4@PLT
.L4:
	movq	-8(%rbp), %rax
	movl	$42, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
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
	.zero	32
	.text
	.globl	set_number
	.type	set_number, @function
set_number:
.LASANPC7:
.LFB7:
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
	je	.L6
	movq	%rax, %rdx
	andl	$3, %edx
	testq	%rdx, %rdx
	je	.L7
.L6:
	movq	%rax, %rsi
	leaq	.Lubsan_data2(%rip), %rax
	movq	%rax, %rdi
	call	__ubsan_handle_type_mismatch_v1@PLT
.L7:
	movq	-8(%rbp), %rax
	movq	%rax, %rdx
	shrq	$3, %rdx
	addq	$2147450880, %rdx
	movzbl	(%rdx), %edx
	testb	%dl, %dl
	setne	%sil
	movq	%rax, %rcx
	andl	$7, %ecx
	addl	$3, %ecx
	cmpb	%dl, %cl
	setge	%dl
	andl	%esi, %edx
	testb	%dl, %dl
	je	.L8
	movq	%rax, %rdi
	call	__asan_report_load4@PLT
.L8:
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	set_number, .-set_number
	.section	.rodata
	.align 32
.LC1:
	.string	"value=%d\n"
	.zero	54
	.text
	.globl	main
	.type	main, @function
main:
.LASANPC8:
.LFB8:
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
.LFE8:
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
	.zero	56
	.section	.rodata
.LC2:
	.string	"*.Lubsan_data2"
.LC3:
	.string	"*.Lubsan_data1"
.LC4:
	.string	"*.Lubsan_type0"
.LC5:
	.string	"*.Lubsan_data0"
.LC6:
	.string	"*.LC1"
.LC7:
	.string	"*.LC0"
	.section	.data.rel.local
	.align 32
	.type	.LASAN0, @object
	.size	.LASAN0, 384
.LASAN0:
	.quad	.Lubsan_data2
	.quad	32
	.quad	64
	.quad	.LC2
	.quad	.LC0
	.quad	0
	.quad	0
	.quad	0
	.quad	.Lubsan_data1
	.quad	32
	.quad	64
	.quad	.LC3
	.quad	.LC0
	.quad	0
	.quad	0
	.quad	0
	.quad	.Lubsan_type0
	.quad	10
	.quad	64
	.quad	.LC4
	.quad	.LC0
	.quad	0
	.quad	0
	.quad	0
	.quad	.Lubsan_data0
	.quad	40
	.quad	96
	.quad	.LC5
	.quad	.LC0
	.quad	0
	.quad	0
	.quad	0
	.quad	.LC1
	.quad	10
	.quad	64
	.quad	.LC6
	.quad	.LC0
	.quad	0
	.quad	0
	.quad	0
	.quad	.LC0
	.quad	7
	.quad	64
	.quad	.LC7
	.quad	.LC0
	.quad	0
	.quad	0
	.quad	0
	.text
	.type	_sub_D_00099_0, @function
_sub_D_00099_0:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$6, %esi
	leaq	.LASAN0(%rip), %rax
	movq	%rax, %rdi
	call	__asan_unregister_globals@PLT
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	_sub_D_00099_0, .-_sub_D_00099_0
	.section	.fini_array.00099,"aw"
	.align 8
	.quad	_sub_D_00099_0
	.text
	.type	_sub_I_00099_1, @function
_sub_I_00099_1:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	__asan_init@PLT
	call	__asan_version_mismatch_check_v8@PLT
	movl	$6, %esi
	leaq	.LASAN0(%rip), %rax
	movq	%rax, %rdi
	call	__asan_register_globals@PLT
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	_sub_I_00099_1, .-_sub_I_00099_1
	.section	.init_array.00099,"aw"
	.align 8
	.quad	_sub_I_00099_1
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

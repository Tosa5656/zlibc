bits 64

global _start

extern __libc_start_main

section .text
_start:
	xor rbp, rbp

	mov rdi, [rsp]
	lea rsi, [rsp + 8]

	call __libc_start_main
.halt:
	hlt
	jmp .halt

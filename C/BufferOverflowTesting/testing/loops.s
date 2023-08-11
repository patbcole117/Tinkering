global _start

section .text
_start:
    mov rax, 2
    mov rcx, 5
loop:
    imul rax, rax
    loop loop

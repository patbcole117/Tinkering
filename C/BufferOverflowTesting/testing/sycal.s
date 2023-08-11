global _start

section .text
_start:
    mov rbp, rsp
open:
    call clear
    ; push le
    mov rax, 0x656C
    push rax
    xor rax, rax
    ; push ifpmet/.
    mov rax, QWORD 0x6966706D65742F2E
    push rax
    xor rax, rax

    mov  al, 2
    mov rdi, rsp ; ./tempfile
    mov sil, 1
    syscall
    call exit

clear:
    xor rax, rax
    xor rdi, rdi
    xor rsi, rsi
    ret

exit:
    xor rax, rax
    xor rdi, rdi
    mov al, 60
    syscall


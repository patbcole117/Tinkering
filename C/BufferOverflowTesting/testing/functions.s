global  _start
extern  printf

section .data
    outFormat db  "It's %s", 0x0a, 0x00
    message db "Aligned!", 0x0a

section .text
_start:
    call print          ; print string
    call Exit           ; Exit the program

print:
    mov rdi, outFormat  ; set 1st argument (Print Format)
    mov rsi, message    ; set 2nd argument (message)
    sub rsp, 8
    call printf         ; printf(outFormat, message)
    ret

Exit:
    mov rax, 60
    mov rdi, 0
    syscall

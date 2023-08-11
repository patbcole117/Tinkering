global _start
extern printf, scanf

section .data
    message db "Please input max fn", 0x0a
    inFormat db "%d", 0x00
    outFormat db "%d", 0x0a, 0x00
    
section .bss
    userInput resb 1

section .text
_start:
    call printMessage
    call getInput
    call initFib
    call loopFib
    call Exit

getInput:
   mov rdi, inFormat
   mov rsi, userInput
   sub rsp, 8
   call scanf
   add rsp, 8
   ret

printMessage:
    mov rax, 1          ;rax: syscall number 1 (write)
    mov rdi, 1          ;rdi: fd for stdout
    push message        ;push message on the stack
    pop rsi             ;pop the stack pointer into rsi
    mov rdx, 20         ;rdx length of 20 bytes
    syscall
    ret

initFib:
    xor rax, rax
    xor rbx, rbx
    inc rbx
    ret

printFib:
    push rax
    push rbx
    mov rdi, outFormat  ;load the print format into rdi
    mov rsi, rbx        ;load fib number into rsi
    call printf         ;printf(outFormat, rsi)
    pop rbx
    pop rax
    ret

loopFib:
    call printFib
    add rax, rbx
    xchg rax, rbx
    cmp rbx, [userInput]
    js loopFib
    ret

Exit:
    mov rax, 60          ;rax syscall number 60 (exit)
    mov rdi, 0          ;status codearg 0 moved to rdi
    syscall

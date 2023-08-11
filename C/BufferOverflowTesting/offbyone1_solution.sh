#!/bin/bash

#The vulnerability is related to the loop on line 14. This loop
#is a classic example of an Off-By-One buffer overflow.
#" buffer " is only 128 bytes long. However the loop will copy
#129 bytes into it. The last byte will overflow into " s2 ".

#By line 18 the stack looks as follows:

# $rbp = 0x7fffffffe260 
# 0x7fffffffe248  " s1 "          0x402004 : "/bin/ls"
# 0x7fffffffe240  " s2 "          0x40200c : "/bin/ps"
# 0x7fffffffe238  buffer[127]
# 0x7fffffffe1c0  buffer[0]
# $rsp = 0x7fffffffe1b0     

#Notice that " buffer " is directly next to " s2 ". This means
#the overvlowed byte will overwrite the least-significant byte 
#of " s2 ".

#When ran with no arguments, This program will execute 
#" /bin/ps " however by injecting \x04 into " s2 " we can get
#the program to instead execute " /bin/ls ".

#Note the loop will always copy 129 bytes regardless of the 
#length of " buffer ". This causes random behavior when 
#arguments are passed < 129 bytes in length; since the loop 
#will continue copying bytes after argv[1].

./offbyone1 $(python3 -c 'print("A"*128+b"\x04".decode())')

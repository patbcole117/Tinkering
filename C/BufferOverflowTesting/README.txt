gcc:
    -fno-stack-protector
    -no-pie
    -z execstack
    -z norelro
    -g
    -m64
    -o <filename>
    <filename>.c

checksec <filename>

gdb:
    env -i HOME=$HOME PATH=$PATH PWD=$PWD SHELL=$SHELL SHLVL=0 <fullpathtofile>
    unset env LINES
    unset env COLUMNS

gdb adds around 112bytes to address.

pwntools:
    write cyclyc(cyclic_find(
    write add
    write nops
    write payload

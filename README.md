Mimo 🛰️

A tiny, 3-instruction bytecode interpreter built with Freestanding C. It bypasses glibc entirely, using raw x86_64 syscalls to talk to the Linux kernel for a sub-10KB binary footprint.
How it works:

    > : Move the bit pointer (wraps at 8).

    + : Flip the bit at the current pointer.

    . : Print the buffer as ASCII and reset everything.

Usage:

    Build it:
    Bash

    gcc -nostdlib -static -Os -s -fno-stack-protector tiny_mimo.c -o mimo

    Run your code:
    Bash

    ./mimo input.mimo

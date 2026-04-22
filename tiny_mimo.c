/* Syscall numbers for x86_64 */
#define SYS_read 0
#define SYS_write 1
#define SYS_open 2
#define SYS_exit 60

/* A tiny wrapper for syscalls */
long syscall3(long num, long a1, long a2, long a3) {
    long ret;
    __asm__ volatile ("syscall" : "=a"(ret) : "a"(num), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11", "memory");
    return ret;
}

void _start() {
    // On entry, the stack contains argc, then argv pointers.
    // This is a bit of low-level magic to get argv[1]
    void **stack = (void **)__builtin_frame_address(0);
    int argc = *(int *)(stack + 1); 
    if (argc < 2) syscall3(SYS_exit, 1, 0, 0);

    char **argv = (char **)(stack + 2);
    int fd = syscall3(SYS_open, (long)argv[1], 0, 0); // 0 = O_RDONLY
    if (fd < 0) syscall3(SYS_exit, 1, 0, 0);

    unsigned char buf = 0;
    int ptr = 0;
    char c;

    while (syscall3(SYS_read, fd, (long)&c, 1) > 0) {
        if (c == '>') ptr = (ptr + 1) % 8;
        else if (c == '+') buf ^= (1 << (7 - ptr));
        else if (c == '.') {
            syscall3(SYS_write, 1, (long)&buf, 1);
            buf = 0;
            ptr = 0;
        }
    }

    syscall3(SYS_exit, 0, 0, 0);
}

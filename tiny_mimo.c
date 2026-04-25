/* Syscall numbers for x86_64 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
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
long get_pos(int fd) {
	return syscall3(8, fd, 0, 1);
}
void set_pos(int fd, long pos) {
	syscall3(8,fd,pos,0);
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

    unsigned char buf[300];
    memset(buf, 48, 300);
    int ptr = 0, mov = 1;
    off_t loop_pos=-1;
    char c;

    while (syscall3(SYS_read, fd, (long)&c, 1) > 0) {
        if (c == '>') mov==1?ptr++:ptr--;
        else if (c == '+') buf[ptr]=mov==1?++buf[ptr]:--buf[ptr];
        else if (c == ':') loop_pos = get_pos(fd);
        else if (c == '?') {
		if (buf[ptr]>48 && loop_pos!=-1) {
			set_pos(fd, loop_pos);
		}
	}
        else if (c == '^') mov=-mov;
        else if (c == '.') syscall3(SYS_write, 1, (long)&buf, 1);
    }

    syscall3(SYS_exit, 0, 0, 0);
}

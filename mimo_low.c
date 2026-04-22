#include <linux/nolibc.h>

void _start(int argc, char *argv[]) {
    if (argc < 2) exit(1);

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) exit(1);

    unsigned char buf = 0;
    int ptr = 0;
    char c;

    while (read(fd, &c, 1) > 0) {
        if (c == '>') {
            ptr = (ptr + 1) % 8;
        } else if (c == '+') {
            buf ^= (1 << (7 - ptr));
        } else if (c == '.') {
            write(1, &buf, 1);
            buf = 0;
            ptr = 0;
        }
    }

    close(fd);
    exit(0);
}

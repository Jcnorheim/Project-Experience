#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    char r[512];

    if ( (fd = open("/dev/scullbuffer", O_RDONLY)) == -1 ) {
        perror("open(/dev/scullbuffer)");
        exit(1);
    }

    while (1) {
        memset(r, 0, sizeof(r));
        read(fd, r, 512);
        printf("consumer: %s\n", r);
    }

    return 0;
}
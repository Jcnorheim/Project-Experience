
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;

    if (argc != 2) {
        printf("usage: ./producer <string to produce>\n");
        exit(1);
    }

    if ( (fd = open("/dev/scullbuffer", O_WRONLY)) == -1 ) {
        perror("open(/dev/scullbuffer)");
        exit(1);
    }

    while (1) {
        write(fd, argv[1], strlen(argv[1]));
        sleep(1);
    }

    return 0;
}
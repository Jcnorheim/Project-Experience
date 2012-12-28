/*  readInput.cpp
    Author: Mark Mackey     4004242
    Date:   October 5, 2011

    File containing functions to read in a file
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char *readInput (int argc, char **argv) {

    // need at least 2 arguments 
    if (argc <= 1) {
        printf ("Usage: %s <filename>\n", argv[0]);
        return NULL;
    }

    FILE *in_fp;
    in_fp = fopen(argv[1],"r");
    if (in_fp == NULL) {
        printf ("cannot access %s: No such file or directory\n", argv[1]);
        return NULL;
    }

    // Determine file size
    struct stat filestatus;
    stat (argv[1], &filestatus);

    int filesize = filestatus.st_size + 1;

    // Allocate space for char buffer.
    char *buffer = (char *) malloc( sizeof(char) * filesize);

    int index = 0;
    char ch = getc(in_fp);

    // Read it in
    while (ch != EOF) {
        buffer[index] = ch;
        index++;
        ch = getc(in_fp);
    }
    buffer[index] = '\0';

    return buffer;
}

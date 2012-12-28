#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <string>
#include "parser.h"

void outLog(const char* message);

inline void outLog(const char* message) {
    int DEBUG = 0;
    if (DEBUG) {
        printf("%s", message);
    }
}


#endif // DEBUG_H

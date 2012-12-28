/*  translator.cpp
    Author: Mark Mackey     4004242
    Date:   October 5, 2011 

    File containing main function for project
*/

#include <stdlib.h>

#include "readInput.h"
#include "scanner.h"
#include "parser.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
    const char *buffer = readInput(argc, argv);

    Parser p;
    ParseResult pr = p.parse( buffer );

    ofstream file;
    file.open ("unparse.wtf");
    file << pr.ast->unparse();
    file.close();
    ofstream file2;
    file2.open ("program.cpp");
    file2 << pr.ast->cppCode();
    file2.close();

    pr.FreeAST();

    return 0;
}

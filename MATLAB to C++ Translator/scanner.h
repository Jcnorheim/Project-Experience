/* This enumerated type is used to keep track of what kind of
   construct was matched. 
*/
#ifndef SCANNER_H
#define SCANNER_H

enum tokenEnumType { 
    // Keywords
    integerKwd, floatKwd, booleanKwd, stringKwd, matrixKwd,
    letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd, 
    forKwd, toKwd, printKwd,

    // Names
    varName, 

    // Constants
    integerConst, floatConst, stringConst, booleanConst,

    // Punctuation
    comma, semiColon, 
    leftParen, rightParen, leftCurly, rightCurly, leftSquare, rightSquare,

    // Operators
    assignment,  // was 'equals'
    add, multiply, subtract, divide,
    lessThan, lessThanEqual, greaterThan, greaterThanEqual, 
    equalTo, notEqualTo,

    andOp, orOp, notOp,
    blockComment, lineComment,
    noMatch,
    lexicalError,
    endOfFile
} ;
typedef enum tokenEnumType tokenType ;


struct tokenStruct {
    tokenType terminal;
    char *lexeme;
    char *data;
    int length;
    int line;
    int column;
    tokenStruct *next;
};
typedef struct tokenStruct token ;

token *scan (const char *text) ;

const char *getTokenTypeName (tokenType tt) ;

#endif

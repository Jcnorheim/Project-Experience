/*  scanner.cpp
    Author: Mark Mackey     4004242
    Date:   October 5, 2011

    File containing most of the code for scanner functionality
*/

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>

#include "readInput.h"

const int NUMTOKENS = 43;

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
typedef struct tokenStruct token;

int linenum = 1;
int charnum = 1;


void printTokenList(token *t);

void makeTokenStruct(token *t, tokenType term, const char *lex, char *data, int length, int line, int column);

void addToTokenList(token *t, tokenType term, const char *lex, char *data, int length, int line, int column);

int matchWSandComments(regex_t *whitespace,
                        regex_t *blockComment,
                        const char *text);

int matchRegex(regex_t *regex, const char *text, char *capture);

void createRegex(regex_t *regex, const char *pattern);

void updatePosition(const char *text, int characters);

const char *getTokenTypeName(tokenType type);

void cat(char *buffer);

token *scan(const char *text);

void strcpy(char *s, char *t) {
    while (*s++ = *t++) ;
}

token *scan(const char *text) {
    if (text == NULL) {
        return NULL;
    }

    // struct for pairing tokenTypes with Regexes
    struct regexToken {
        tokenType type;
        regex_t regex;
    } RTset[NUMTOKENS];

    // RTset is array of struct regexToken, the order of RTset
    // gives priority for later
    int index = 0;

    // Compile regular expressions
    regex_t r_whiteSpace;
    createRegex(&r_whiteSpace, "^[\n\t\r ]+");

    regex_t r_blockComment;
    createRegex(&r_blockComment, "^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");

    regex_t r_floatConst;
    createRegex(&r_floatConst, "^([0-9]+\\.[0-9]+)");
    RTset[index].type = floatConst; RTset[index].regex = r_floatConst; index++;

    regex_t r_integerConst;
    createRegex(&r_integerConst, "^([0-9]+)");
    RTset[index].type = integerConst; RTset[index].regex = r_integerConst; index++;

    regex_t r_stringConst;
    createRegex(&r_stringConst, "^\"[^\"]+\"");
    RTset[index].type = stringConst; RTset[index].regex = r_stringConst; index++;

    regex_t r_booleanConst;
    createRegex(&r_booleanConst, "^(true|false)");
    RTset[index].type = booleanConst; RTset[index].regex = r_booleanConst; index++;

    regex_t r_leftParen;
    createRegex(&r_leftParen, "^\\(");
    RTset[index].type = leftParen; RTset[index].regex = r_leftParen; index++;

    regex_t r_rightParen;
    createRegex(&r_rightParen, "^\\)");
    RTset[index].type = rightParen; RTset[index].regex = r_rightParen; index++;

    regex_t r_leftCurly;
    createRegex(&r_leftCurly, "^\\{");
    RTset[index].type = leftCurly; RTset[index].regex = r_leftCurly; index++;

    regex_t r_rightCurly;
    createRegex(&r_rightCurly, "^\\}");
    RTset[index].type = rightCurly; RTset[index].regex = r_rightCurly; index++;

    regex_t r_leftSquare;
    createRegex(&r_leftSquare, "^\\[");
    RTset[index].type = leftSquare; RTset[index].regex = r_leftSquare; index++;

    regex_t r_rightSquare;
    createRegex(&r_rightSquare, "^\\]");
    RTset[index].type = rightSquare; RTset[index].regex = r_rightSquare; index++;

    regex_t r_assignment;
    createRegex(&r_assignment, "^\\=");
    RTset[index].type = assignment; RTset[index].regex = r_assignment; index++;

    regex_t r_lessThanEqual;
    createRegex(&r_lessThanEqual, "^<=");
    RTset[index].type = lessThanEqual; RTset[index].regex = r_lessThanEqual; index++;

    regex_t r_greaterThanEqual;
    createRegex(&r_greaterThanEqual, "^>=");
    RTset[index].type = greaterThanEqual; RTset[index].regex = r_greaterThanEqual; index++;

    regex_t r_greaterThan;
    createRegex(&r_greaterThan, "^>");
    RTset[index].type = greaterThan; RTset[index].regex = r_greaterThan; index++;

    regex_t r_lessThan;
    createRegex(&r_lessThan, "^<");
    RTset[index].type = lessThan; RTset[index].regex = r_lessThan; index++;

    regex_t r_equalTo;
    createRegex(&r_equalTo, "^==");
    RTset[index].type = equalTo; RTset[index].regex = r_equalTo; index++;

    regex_t r_notEqualTo;
    createRegex(&r_notEqualTo, "^!=");
    RTset[index].type = notEqualTo; RTset[index].regex = r_notEqualTo; index++;

    regex_t r_andOp;
    createRegex(&r_andOp, "^\\&\\&");
    RTset[index].type = andOp; RTset[index].regex = r_andOp; index++;

    regex_t r_orOp;
    createRegex(&r_orOp, "^\\|\\|");
    RTset[index].type = orOp; RTset[index].regex = r_orOp; index++;

    regex_t r_notOp;
    createRegex(&r_notOp, "^!");
    RTset[index].type = notOp; RTset[index].regex = r_notOp; index++;

    regex_t r_add;
    createRegex(&r_add, "^\\+");
    RTset[index].type = add; RTset[index].regex = r_add; index++;

    regex_t r_subtract;
    createRegex(&r_subtract, "^\\-");
    RTset[index].type = subtract; RTset[index].regex = r_subtract; index++;

    regex_t r_multiply;
    createRegex(&r_multiply, "^\\*");
    RTset[index].type = multiply; RTset[index].regex = r_multiply; index++;

    regex_t r_divide;
    createRegex(&r_divide, "^\\/");
    RTset[index].type = divide; RTset[index].regex = r_divide; index++;

    regex_t r_semiColon;
    createRegex(&r_semiColon, "^\\;");
    RTset[index].type = semiColon; RTset[index].regex = r_semiColon; index++;

    regex_t r_comma;
    createRegex(&r_comma, "^\\,");
    RTset[index].type = comma; RTset[index].regex = r_comma; index++;

    regex_t r_integerKwd;
    createRegex(&r_integerKwd, "^Integer");
    RTset[index].type = integerKwd; RTset[index].regex = r_integerKwd; index++;

    regex_t r_printKwd;
    createRegex(&r_printKwd, "^print");
    RTset[index].type = printKwd; RTset[index].regex = r_printKwd; index++;

    regex_t r_booleanKwd;
    createRegex(&r_booleanKwd, "^Boolean");
    RTset[index].type = booleanKwd; RTset[index].regex = r_booleanKwd; index++;

    regex_t r_stringKwd;
    createRegex(&r_stringKwd, "^String");
    RTset[index].type = stringKwd; RTset[index].regex = r_stringKwd; index++;

    regex_t r_floatKwd;
    createRegex(&r_floatKwd, "^Float");
    RTset[index].type = floatKwd; RTset[index].regex = r_floatKwd; index++;

    regex_t r_forKwd;
    createRegex(&r_forKwd, "^for");
    RTset[index].type = forKwd; RTset[index].regex = r_forKwd; index++;

    regex_t r_inKwd;
    createRegex(&r_inKwd, "^in");
    RTset[index].type = inKwd; RTset[index].regex = r_inKwd; index++;

    regex_t r_endKwd;
    createRegex(&r_endKwd, "^end");
    RTset[index].type = endKwd; RTset[index].regex = r_endKwd; index++;

    regex_t r_toKwd;
    createRegex(&r_toKwd, "^to");
    RTset[index].type = toKwd; RTset[index].regex = r_toKwd; index++;

    regex_t r_letKwd;
    createRegex(&r_letKwd, "^let");
    RTset[index].type = letKwd; RTset[index].regex = r_letKwd; index++;

    regex_t r_matrixKwd;
    createRegex(&r_matrixKwd, "^Matrix");
    RTset[index].type = matrixKwd; RTset[index].regex = r_matrixKwd; index++;

    regex_t r_ifKwd;
    createRegex(&r_ifKwd, "^if");
    RTset[index].type = ifKwd; RTset[index].regex = r_ifKwd; index++;

    regex_t r_thenKwd;
    createRegex(&r_thenKwd, "^then");
    RTset[index].type = thenKwd; RTset[index].regex = r_thenKwd; index++;

    regex_t r_elseKwd;
    createRegex(&r_elseKwd, "^else");
    RTset[index].type = elseKwd; RTset[index].regex = r_elseKwd; index++;

    regex_t r_varName;
    createRegex(&r_varName, "^([a-zA-Z_][a-zA-Z0-9_]*)");
    RTset[index].type = varName; RTset[index].regex = r_varName; index++;

    regex_t r_lineComment;
    createRegex(&r_lineComment, "^\\/\\/[^\n]+");
    RTset[index].type = lineComment; RTset[index].regex = r_lineComment; index++;

    regex_t r_lexicalError;
    createRegex(&r_lexicalError, "^[@%$]+");
    RTset[index].type = lexicalError; RTset[index].regex = r_lexicalError; index++;

    int numMatched = 0;
    int maxNumMatched = 0;
    int RTsetIndex = 0;
    char capture[512];
    char maxCapture[512];
    tokenType matchType = noMatch;

    token *headToken = NULL;

    // ignore initial whitespace/comments
    numMatched = matchWSandComments(&r_whiteSpace, &r_blockComment, text);
    updatePosition(text, numMatched);       // Move position past whitespace/comments

    text += numMatched;

    // loop over text file
    while (text[0] != '\0') {
        maxNumMatched = 0;
        numMatched = 0;
        matchType = noMatch;
        RTsetIndex = 0;

        // loop through tokens taking greatest match
        while(RTsetIndex < NUMTOKENS) {
            numMatched = matchRegex(&RTset[RTsetIndex].regex, text, capture);
            if (numMatched > maxNumMatched) {
                maxNumMatched = numMatched;
                strcpy(maxCapture, capture);
                matchType = RTset[RTsetIndex].type;
            }
            RTsetIndex++;
        }

        if (matchType == lineComment) {
            updatePosition(text, maxNumMatched);
            text += maxNumMatched;
            continue;
        }

        if (matchType == noMatch) {
            text += 1;
            updatePosition(text, 1);
        }
        else {
            if (headToken == NULL) {
                headToken = (token *) malloc(sizeof(token));
                makeTokenStruct(headToken, matchType, getTokenTypeName(matchType), &maxCapture[0], maxNumMatched, linenum, charnum);
            }
            else {
                addToTokenList(headToken, matchType, getTokenTypeName(matchType), &maxCapture[0], maxNumMatched, linenum, charnum);
                updatePosition(text, maxNumMatched);
            }
            text += maxNumMatched;
        }

        numMatched = matchWSandComments(&r_whiteSpace, &r_blockComment, text);
        updatePosition(text, numMatched);
        text += numMatched;

    }

    matchType = endOfFile;
    if (headToken == NULL) {
        headToken = (token *) malloc(sizeof(token));
        makeTokenStruct(headToken, matchType, getTokenTypeName(matchType), (char *) " ", 0, linenum, charnum);
    }
    else {
        addToTokenList(headToken, matchType, getTokenTypeName(matchType), (char *) " ", 0, linenum, charnum);
    }

//    printTokenList(headToken);

    return headToken;
}

void makeTokenStruct(token *t, tokenType term, const char *lex, char *data, int length, int line, int column) {
    char *dathold = (char *) malloc(sizeof(char) * length);
    strcpy(dathold, data);
    char *lexhold = (char *) malloc(50 * sizeof(char));
    strcpy(lexhold, (char *)lex);

    t->terminal = term;
    t->lexeme = lexhold;
    t->data = dathold;
    t->length = length;
    t->line = line;
    t->column = column;
    t->next = t;
}

void printTokenList(token *t) {
    printf("%s", t->lexeme);
    tokenType type = t->terminal;
    if (type == integerConst || type == varName || type == stringConst || type == floatConst || type == lexicalError) {
        printf(" \"%s\"", t->data);
    }
    printf("\n");
    if (t->next != t) {
        printTokenList(t->next);
    }
}

void addToTokenList(token *t, tokenType term, const char *lex, char *data, int length, int line, int column) {
    if (t->next == t) {
        token *t2 = (token *) malloc(sizeof(token));
        makeTokenStruct(t2, term, lex, data, length, line, column);
        t->next = t2;
    }
    else {
        addToTokenList(t->next, term, lex, data, length, line, column);
    }
}

const char *getTokenTypeName(tokenType type) {
    switch (type) {
        case leftParen: return (const char *) "leftParen\0"; break;
        case rightParen: return (const char *) "rightParen\0"; break;
        case leftCurly: return (const char *) "leftCurly\0"; break;
        case rightCurly: return (const char *) "rightCurly\0"; break;
        case leftSquare: return (const char *) "leftSquare\0"; break;
        case rightSquare: return (const char *) "rightSquare\0"; break;
        case integerKwd: return (const char *) "integerKwd\0"; break;
        case floatKwd: return (const char *) "floatKwd\0"; break;
        case matrixKwd: return (const char *) "matrixKwd\0"; break;
        case letKwd: return (const char *) "letKwd\0"; break;
        case booleanKwd: return (const char *) "booleanKwd\0"; break;
        case ifKwd: return (const char *) "ifKwd\0"; break;
        case thenKwd: return (const char *) "thenKwd\0"; break;
        case printKwd: return (const char *) "printKwd\0"; break;
        case elseKwd: return (const char *) "elseKwd\0"; break;
        case forKwd: return (const char *) "forKwd\0"; break;
        case stringKwd: return (const char *) "stringKwd\0"; break;
        case inKwd: return (const char *) "inKwd\0"; break;
        case toKwd: return (const char *) "toKwd\0"; break;
        case endKwd: return (const char *) "endKwd\0"; break;
        case assignment: return (const char *) "assignment\0"; break;
        case lessThanEqual: return (const char *) "lessThanEqual\0"; break;
        case greaterThanEqual: return (const char *) "greaterThanEqual\0"; break;
        case greaterThan: return (const char *) "greaterThan\0"; break;
        case lessThan: return (const char *) "lessThan\0"; break;
        case equalTo: return (const char *) "equalTo\0"; break;
        case notEqualTo: return (const char *) "notEqualTo\0"; break;
        case andOp: return (const char *) "andOp\0"; break;
        case orOp: return (const char *) "orOp\0"; break;
        case notOp: return (const char *) "notOp\0"; break;
        case multiply: return (const char *) "multiply\0"; break;
        case divide: return (const char *) "divide\0"; break;
        case add: return (const char *) "add\0"; break;
        case subtract: return (const char *) "subtract\0"; break;
        case integerConst: return (const char *) "integerConst\0"; break;
        case floatConst: return (const char *) "floatConst\0"; break;
        case stringConst: return (const char *) "stringConst\0"; break;
        case booleanConst: return (const char *) "booleanConst\0"; break;
        case semiColon: return (const char *) "semiColon\0"; break;
        case comma: return (const char *) "comma\0"; break;
        case varName: return (const char *) "varName\0"; break;
        case lineComment: return (const char *) "lineComment\0"; break;
        case lexicalError: return (const char *) "lexicalError\0"; break;
        case endOfFile: return (const char *) "endOfFile\0"; break;
    }
    return (const char *) "";
}

void updatePosition(const char *text, int characters) {
    // updates linenum and charnum globals

    while (characters != 0) {
        if (text[0] == '\n') {
            charnum = 1;
            linenum++;
        }
        else {
            charnum++;
        }
        text++;
        characters--;
    }
}

int matchRegex(regex_t *regex, const char *text, char *capture) {
    int status;
    const int nsub = 1;
    regmatch_t matches[nsub];

    status = regexec(regex, text, (size_t)nsub, matches, 0);

    if (status == REG_NOMATCH) {
        return 0;
    }
    else {
        int length = (int) matches[0].rm_eo - (int) matches[0].rm_so;
        if (capture != NULL) {
            int index = 0;
            for (; index < length; index++)
                capture[index] = text[index];
            capture[index] = '\0';
        }

        return length;
    }
}

void createRegex(regex_t *regex, const char *pattern) {
    int rc = 0;

    rc = regcomp(regex, pattern, REG_EXTENDED);

    if (rc != 0) {
        printf("Error compiling regular expression.\n");
        size_t length = regerror (rc, regex, NULL, 0);
        char *buffer = (char *) malloc( sizeof(char) * length);
        (void) regerror (rc, regex, buffer, length);
        printf("%s\n", buffer);
    }
}

int matchWSandComments(regex_t *r_whitespace, regex_t *r_blockComment, const char *text) {
    int matched = 0;
    int matching = 1;
    int total = 0;

    while (matching) {
        matching = 0;

        matched = matchRegex(r_whitespace, text, NULL);
        total += matched;

        // matched some spaces
        if (matched > 0) {
            text += matched;
            matching = 1;       // match stops at newline, need to loop again
        }

        matched = matchRegex(r_blockComment, text, NULL);
        total += matched;

        // matched a comment
        if (matched > 0) {
            text += matched;
            matching = 1;
        }
    }

    return total;
}

void cat(char *buffer) {
    for (int index = 0; buffer[index] != '\0'; index++)
        printf("%d: '%c'\n", index, buffer[index]);
}


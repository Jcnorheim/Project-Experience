#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include "scanner.h"
#include "Node.h"
#include "Root.h"
#include "Statement.h"
#include "Expr.h"
#include "VarName.h"
#include "Assignment.h"
#include "Declaration.h"
#include "AnyConst.h"
#include "BinOpExpr.h"
#include "Debug.h"
#include "IfStmt.h"
#include "Block.h"
#include "PrintStmt.h"
#include "ForStmt.h"
#include "MatrixDecl.h"
#include "FunctionCall.h"
#include "ParenExpr.h"
#include "LetExprObject.h"
#include "IfExprObject.h"
#include "NotExprObject.h"
#include "MatrixRefObject.h"

class ParseResult ;
class Parser ;
class ExprElem ;

const int DEBUG_ = 0;

class ParseResult {
public:
    ParseResult() { ok=true, errors=""; }
    void FreeAST() { delete ast; }
    bool ok ;
    std::string errors ;
    Node *ast;
    std::string pp;
} ;

class Parser {

public:
    ParseResult parse (const char * text) ;

    token *tokens ;
    token *currToken ;
    token *prevToken ;

    bool attemptMatch (tokenType tt) ;
    void match (tokenType tt) ;
    bool nextIs (tokenType tt);

    ExprElem *makeExprElem (token *ct, Parser *p ) ;
    void nextToken() ;

    ParseResult parseRoot ();
    ParseResult parseStmts ();
    ParseResult parseStmt ();
    ParseResult parseDecl ();
    ParseResult parseExpr (int rbp);
    ParseResult parseTypeExpr ();

} ;


class ExprElem {
public:
    ExprElem ( ) : pr(), p(NULL) { }
    ExprElem (  Parser *_p ) : pr(), p(_p) { }

    ParseResult pr ;
    Parser *p ;

    virtual ExprElem *nud() ;
    virtual ExprElem *led(ExprElem*) ;
} ;

class NameConstExprElem : public ExprElem {
public:
    NameConstExprElem ( ) ;
    NameConstExprElem (  Parser *_p ) ;
    virtual ExprElem *nud() ;
} ;

class IntegerConstExprElem : public ExprElem {
public:
    IntegerConstExprElem ( ) ;
    IntegerConstExprElem ( Parser * _p ) ;
    virtual ExprElem *nud();
} ;

class FloatConstExprElem : public ExprElem {
public:
    FloatConstExprElem ( ) ;
    FloatConstExprElem ( Parser * _p ) ;
    virtual ExprElem *nud();
} ;

class StringConstExprElem : public ExprElem {
public:
    StringConstExprElem ( ) ;
    StringConstExprElem ( Parser * _p ) ;
    virtual ExprElem *nud();
} ;

class BooleanConstExprElem : public ExprElem {
public:
    BooleanConstExprElem ( ) ;
    BooleanConstExprElem ( Parser * _p ) ;
    virtual ExprElem *nud();
} ;

class BinaryOperator : public ExprElem {
public:
    int precedence ;
    BinaryOperator ( Parser *_p = NULL, int _precedence = 0 ) ;
    virtual ExprElem *led(ExprElem *left) ;
} ;

class MatrixRef : public BinaryOperator {
public:
    MatrixRef ( Parser *_p = NULL, int _precedence = 0 ) ;
    virtual ExprElem *led(ExprElem *left) ;
} ;

class NestedOrFunctionCall : public BinaryOperator {
public:
    NestedOrFunctionCall ( Parser *_p = NULL, int _precedence = 0 ) ;
    virtual ExprElem *led(ExprElem *left) ;
    virtual ExprElem *nud() ;
} ;

class LetExpr : public ExprElem {
public:
    LetExpr ( Parser *_p = NULL ) ;
    virtual ExprElem *nud() ;
} ;

class IfExpr : public ExprElem {
public:
    IfExpr ( Parser *_p = NULL ) ;
    virtual ExprElem *nud() ;
} ;

class NotExpr : public ExprElem {
public:
    NotExpr ( Parser *_p = NULL ) ;
    virtual ExprElem *nud() ;
} ;


#endif /* PARSER_H */

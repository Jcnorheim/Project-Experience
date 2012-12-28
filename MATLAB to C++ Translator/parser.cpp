/* A recursive descent parser with operator precedence.

   Author: Eric Van Wyk

   This algorithms is based on the work of Douglas Crockford in "Top
   Down Operator Precedence", a chapter in the book "Beautiful Code".
   Mr. Crockford describes in his chapter how his work comes from that
   of Based on algorithms described Vaughan Pratt in "Top Down Operator
   Precedence", presented at the ACM Symposium on Principles of
   Programming Langauges.

   Douglas Crockford's chapter is available at http://javascript.crockford.com/tdop/tdop.html

   Vaughan Pratt's paper is available at http://portal.acm.org/citation.cfm?id=512931

   These are both quite interesting works and worth reading if you
   find the problem of parsing to be an interesting one.

   Last modified: October 20, 2011.
*/

#include "scanner.h"
#include "parser.h"
#include <cassert>
#include <iostream>
#include <stdio.h>
#include "Debug.h"

//extern const int DEBUG_;
//DEBUG_ = 1;

using namespace std ;

string makeErrorMsg ( tokenType tt ) ;

int lbp(tokenType) ;

ParseResult Parser::parse (const char *text) {
    assert (text != NULL) ;

    tokens = scan (text) ;
    assert (tokens != NULL) ;

    currToken = tokens ;

    ParseResult pr ;
    try {
        pr = parseRoot( ) ;
        pr.ok = true; 
        pr.errors = "" ;
    }
    catch (string errMsg) {
        pr.ok = false ;
        printf("ERROR: %s\n", errMsg.c_str());
        pr.errors = errMsg ;
    }

    return pr ;
}


ParseResult Parser::parseRoot () {
    // Root ::= varName '(' ')' '{' Stmts '}'
    ParseResult pr ;

    match(varName);

    VarName *vn = new VarName(new string(prevToken->data));

    match(leftParen) ;
    match(rightParen) ;
    match(leftCurly) ;

    ParseResult prStmts = parseStmts ();
    Statements *ss = dynamic_cast<Statements *>(prStmts.ast);

    pr.ast = new Root ( vn, ss ) ;

    match(rightCurly) ;

//    printf("\n%s\n", pr.ast->unparse().c_str());

    return pr ;
}

ParseResult Parser::parseStmts () {
    // Stmts ::= <<empty>>
    //        | Stmt Stmts
    ParseResult pr ;

    // If the next1token begins a statement, attemp second production.
    if (nextIs(integerKwd) || nextIs(floatKwd) || nextIs(matrixKwd) ||
        nextIs(stringKwd) || nextIs(booleanKwd) ||
        nextIs(ifKwd) || nextIs(printKwd) || nextIs(forKwd) ||
        nextIs(varName) || nextIs(leftCurly) ) {


        ParseResult prStmt = parseStmt() ;

        Statement *s = dynamic_cast<Statement *>(prStmt.ast);
        if (!s) throw ( (string) "Bad cast of Stmt in StmtSeq" );


        ParseResult prStmts = parseStmts();
        Statements *ss = dynamic_cast<Statements *>(prStmts.ast);
        if (!ss) throw ( (string) "Bad cast of Stmts in StmtSeq" );

        pr.ast = new Statements( s, ss );
    }
    else {
        // Do nothing, this parses the empty production
        pr.ast = new Statements();
    }

    return pr ;
}


ParseResult Parser::parseStmt () {
    ParseResult pr ;

    // Stmt ::= Decl 
    if (nextIs(integerKwd) || nextIs(floatKwd) || nextIs(matrixKwd) ||
        nextIs(stringKwd) || nextIs(booleanKwd) ) {
        pr = parseDecl () ;
    }

    // Stmt ::= '{' Stmts '}'
    else if (attemptMatch(leftCurly)) {
        ParseResult prStmts = parseStmts() ;
        Statements *ss = dynamic_cast<Statements *>(prStmts.ast);

        Block *bk = new Block(ss);
        match(rightCurly) ;
        pr.ast = dynamic_cast<Statement *>(bk);
    }

    // Stmt ::= 'if' '(' Expr ')' Stmt 
    // Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    // We match the 'else' to the nearest 'if', thus
    // "if (b1) then if (b2) then S1 else S2" matches the 'else'
    // to the 'if' with condition 'b2'.
    else if ( attemptMatch (ifKwd) ) {
        IfStmt *is;
        match (leftParen);
        ParseResult prExpr = parseExpr (0) ;
        Expr* c = dynamic_cast<Expr *>(prExpr.ast);

        match (rightParen);

        ParseResult prStmt1 = parseStmt () ;
        Statement *t = dynamic_cast<Statement *>(prStmt1.ast);

        if ( attemptMatch (elseKwd) ) {
            ParseResult prStmt2 = parseStmt() ;
            Statement *e = dynamic_cast<Statement *>(prStmt2.ast);

            is = new IfStmt(c, t, e);
        }
        else {
            is = new IfStmt(c, t);
        }

        pr.ast = is;
    }

    // Stmt ::= varName '=' Expr ';'
    else if ( attemptMatch (varName) ) {
        VarName *vn = new VarName(new string(prevToken->data));

        LExpr *lexpr = NULL;
        if (attemptMatch ( leftSquare )) {
            ParseResult prRowExpr = parseExpr (0);
            Expr *r = dynamic_cast<Expr *>(prRowExpr.ast);
            if ( ! r ) throw ((string) "Bad cast in matrix row assignment");

            match ( comma );

            ParseResult prColExpr =  parseExpr (0);
            Expr *c = dynamic_cast<Expr *>(prColExpr.ast);
            if ( ! c) throw ( (string) "Bad cast in matrix col assignment" );

            match ( rightSquare );

            lexpr = new MatrixRefObject(vn, r, c);
        }
        else {
            lexpr = vn;
        }

        match (assignment) ;

        ParseResult prExpr = parseExpr (0);
        Expr *e = dynamic_cast<Expr *>(prExpr.ast);

        pr.ast = new Assignment ( lexpr , e );
        match (semiColon) ;
    }

    // Stmt ::= 'print' '(' Expr ')' ';' 
    else if ( attemptMatch (printKwd) ) {
        match (leftParen) ;

        ParseResult prExpr = parseExpr (0) ;
        Expr *e = dynamic_cast<Expr *>(prExpr.ast);

        pr.ast = new PrintStmt( e );

        match (rightParen) ;
        match (semiColon) ;
    }

    // Stmt ::= 'for' '(' varName '=' Expr 'to' Expr ')' Stmt
    else if ( attemptMatch (forKwd) ) {
        match (leftParen) ;
        match (varName) ;
        VarName *vn = new VarName(new string(prevToken->data));

        match (assignment) ;

        ParseResult prExpr1 = parseExpr(0) ;
        Expr *e1 = dynamic_cast<Expr *>(prExpr1.ast);

        match (toKwd) ;

        ParseResult prExpr2 = parseExpr(0) ;
        Expr *e2 = dynamic_cast<Expr *>(prExpr2.ast);

        match (rightParen) ;

        ParseResult prStmt = parseStmt () ;
        Statement *s = dynamic_cast<Statement *>(prStmt.ast);

        pr.ast = new ForStmt(vn, e1, e2, s);
    }

    // Stmt ::= ';'
    else if ( attemptMatch (semiColon) ) {
        // parsed a skip
    }

    else 
        throw ( makeErrorMsg ( currToken->terminal ) + " while parsing a statement" ) ;

    return pr ;
}



ParseResult Parser::parseDecl () {
    ParseResult pr ;

    // Decl ::= integerKwd varName ';'
    // Decl ::= floatKwd varName ';'
    // Decl ::= stringKwd varName ';'
    // Decl ::= booleanKwd varName ';'
    if (attemptMatch(integerKwd) || attemptMatch(floatKwd) ||
        attemptMatch(stringKwd) || attemptMatch(booleanKwd) ) {
        string *t = new string(prevToken->data);
        match (varName) ;
        VarName *vn = new VarName(new string(prevToken->data));
        match (semiColon) ;
        pr.ast = new Declaration(t, vn);
    }

    // Decl ::= 'Matrix' varName '[' Expr ',' Expr ']' varName ',' varName
    //          '=' Expr ';'
    // Decl ::= 'Matrix' varName '=' Expr ';'
    else if ( attemptMatch (matrixKwd) ) {
        match (varName) ;
        VarName *v = new VarName(new string(prevToken->data ));

        if ( attemptMatch (leftSquare) ) {
            ParseResult pr1 = parseExpr (0) ;
            Expr *e1 = dynamic_cast<Expr *>(pr1.ast);
            match (comma) ;
            ParseResult pr2 = parseExpr (0) ;
            Expr *e2 = dynamic_cast<Expr *>(pr2.ast);
            match (rightSquare) ;
            match (varName) ;
            VarName *v0 = new VarName(new string(prevToken->data));
            match (comma) ;
            match (varName) ;
            VarName *v1 = new VarName(new string(prevToken->data));
            match (assignment) ;  // was 'equals'
            ParseResult pr3 = parseExpr (0) ;
            Expr *e3 = dynamic_cast<Expr *>(pr3.ast);
            match (semiColon) ;

            pr.ast = new MatrixDecl(v, e1, e2, v0, v1, e3);
        }
        else {
            match (assignment) ;  // was 'equals'
            ParseResult pr0 = parseExpr (0) ;
            Expr *e1 = dynamic_cast<Expr *>(pr0.ast);
            pr.ast = new MatrixDecl(v, e1);
            match (semiColon) ;
        }
    }

    else 
        throw ( makeErrorMsg ( currToken->terminal ) + " while parsing a declaration" ) ;
    return pr ;
}

ParseResult Parser::parseExpr (int rbp) {
    ExprElem *ee = makeExprElem ( currToken, this ) ;
    ExprElem *left = ee->nud() ;
   
    while (rbp < lbp(currToken->terminal) ) {
        ee = makeExprElem ( currToken, this) ;
        left = ee->led(left) ;
    }
    return left->pr ;
}

// This function creates the appropriate ExprElem based on the token type. 
ExprElem *Parser::makeExprElem (token *ct, Parser *p) {

    nextToken() ;
    switch (ct->terminal) {
    case varName: return new NameConstExprElem (p) ;
    case integerConst: return new IntegerConstExprElem (p) ;
    case stringConst: return new StringConstExprElem (p) ;
    case floatConst: return new FloatConstExprElem (p) ;
    case booleanConst: return new BooleanConstExprElem (p) ;

    case andOp: return new BinaryOperator (p, lbp(andOp) ) ;
    case orOp: return new BinaryOperator (p, lbp(orOp) ) ;

    case equalTo: return new BinaryOperator (p, lbp(equalTo) ) ; 
    case notEqualTo: return new BinaryOperator (p, lbp(notEqualTo) ) ; 
    case lessThan: return new BinaryOperator (p, lbp(lessThan) ) ; 
    case lessThanEqual: return new BinaryOperator (p, lbp(lessThanEqual) ) ; 
    case greaterThan: return new BinaryOperator (p, lbp(greaterThan) ) ; 
    case greaterThanEqual: return new BinaryOperator (p, lbp(greaterThanEqual) ) ;

    case add: return new BinaryOperator (p, lbp(add) ) ; 
    case subtract: return new BinaryOperator (p, lbp(subtract) ) ; 

    case multiply: return new BinaryOperator (p, lbp(multiply) ) ; 
    case divide: return new BinaryOperator (p, lbp(divide) ) ; 

    case letKwd: return new LetExpr (p ) ; 
    case ifKwd: return new IfExpr (p ) ; 
    case notOp: return new NotExpr (p ) ; 

    case leftSquare: return new MatrixRef (p, lbp(leftSquare) ) ; 
    case leftParen: return new NestedOrFunctionCall (p, lbp(leftParen) ) ; 

    default: throw ( (string) "problem ..." + getTokenTypeName(ct->terminal) ) ;
    }
}

string makeErrorMsg ( tokenType tt ) {
    printf ("hey woa we got problems\n");
    return (std::string) "Unexpected symbol or problem parsing on " + getTokenTypeName ( tt ) ; 
}

/* Below are the constructors and methods for the different expression
   elements.  This vary based how the various operators, keywords,
   constants, and variable names should be parsed.
 */
ExprElem *ExprElem::nud() {
    throw ( makeErrorMsg ( p->currToken->terminal ) ) ;
}

ExprElem *ExprElem::led(ExprElem*) { 
    throw ( makeErrorMsg ( p->currToken->terminal ) ) ;
}


// VarName
NameConstExprElem::NameConstExprElem ( ) : ExprElem() { }
NameConstExprElem::NameConstExprElem (  Parser *_p ) : ExprElem(_p) { }
ExprElem *NameConstExprElem::nud() {
    VarName *vn = new VarName(new string(p->prevToken->data));
    if (DEBUG_) { printf("making new VarName(%s)\n", p->prevToken->data); };
    pr.ast = vn;

    return this ; 
}

IntegerConstExprElem::IntegerConstExprElem ( ) : ExprElem() { }
IntegerConstExprElem::IntegerConstExprElem (  Parser *_p ) : ExprElem(_p) { 
}
ExprElem *IntegerConstExprElem::nud() {
    if (DEBUG_) { printf("making new AnyConst(%s)\n", p->prevToken->data); };
    pr.ast = new AnyConst (new string( p->prevToken->data )) ; 
    return this ; 
}

FloatConstExprElem::FloatConstExprElem ( ) : ExprElem() { }
FloatConstExprElem::FloatConstExprElem (  Parser *_p ) : ExprElem(_p) { 
}
ExprElem *FloatConstExprElem::nud() {
    if (DEBUG_) { printf("making new AnyConst(%s)\n", p->prevToken->data); };
    pr.ast = new AnyConst (new string( p->prevToken->data )) ; 
    return this ; 
}

StringConstExprElem::StringConstExprElem ( ) : ExprElem() { }
StringConstExprElem::StringConstExprElem (  Parser *_p ) : ExprElem(_p) { 
}
ExprElem *StringConstExprElem::nud() {
    if (DEBUG_) { printf("making new AnyConst(%s)\n", p->prevToken->data); };
    pr.ast = new AnyConst (new string( p->prevToken->data )) ; 
    return this ; 
}

BooleanConstExprElem::BooleanConstExprElem ( ) : ExprElem() { }
BooleanConstExprElem::BooleanConstExprElem (  Parser *_p ) : ExprElem(_p) { 
}
ExprElem *BooleanConstExprElem::nud() {
    if (DEBUG_) { printf("making new AnyConst(%s)\n", p->prevToken->data); };
    pr.ast = new AnyConst (new string( p->prevToken->data )) ; 
    return this ; 
}

// BinaryOperator
// Expr ::= Expr '+' Expr
/* Also used for - * / > >= < <= == != && ||  
   All are left associative with precedence arranged as follows
   from lower to higher precedence
   * /
   + -   
   == != < <= > >=
   || &&
*/
BinaryOperator::BinaryOperator ( Parser *_p , int _precedence )
    : ExprElem(_p), precedence(_precedence) { }
ExprElem *BinaryOperator::led(ExprElem *left) {

    Expr *leftExpr = dynamic_cast<Expr *>(left->pr.ast);
    if ( ! leftExpr )
        throw ( (string) "Bad cast of left Expr in BinaryOperator" );

    string *Op = new string(p->prevToken->data);

    ParseResult prExpr = p->parseExpr ( precedence );
    Expr *rightExpr = dynamic_cast<Expr *>(prExpr.ast);
    if ( ! rightExpr )
        throw ( (string) "Bad cast of right Expr in BinaryOperator" );

    pr.ast = new BinOpExpr ( leftExpr, Op, rightExpr );

    return this ;
}

// MatrixRef
// Expr ::= varName '[' Expr ',' Expr ']'
MatrixRef::MatrixRef ( Parser *_p , int _precedence ) 
    : BinaryOperator(_p, _precedence) { }
ExprElem *MatrixRef::led(ExprElem *left) {
    VarName *vn = dynamic_cast<VarName *>(left->pr.ast);

    ParseResult prExpr1 = p->parseExpr( 0 ) ;
    Expr *e1 = dynamic_cast<Expr *>(prExpr1.ast);

    p->match(comma) ;

    ParseResult prExpr2 = p->parseExpr( 0 ) ;
    Expr *e2 = dynamic_cast<Expr *>(prExpr2.ast);

    p->match(rightSquare) ;
    pr.ast = new MatrixRefObject( vn, e1, e2 );

    return this ; 
}


// NestedOrFunctionCall
NestedOrFunctionCall::NestedOrFunctionCall ( Parser *_p, int _precedence ) 
    : BinaryOperator(_p, _precedence) { }
// Expr ::= varName '(' Expr ')'
ExprElem *NestedOrFunctionCall::led(ExprElem *left) {
    VarName *vn = dynamic_cast<VarName *>(left->pr.ast);

    ParseResult prExpr = p->parseExpr(0) ;
    Expr *exp = dynamic_cast<Expr *>(prExpr.ast);

    pr.ast = new FunctionCall( vn, exp);

    p->match(rightParen) ;
    return this ; 
}
// Expr ::= '(' Expr ')'
ExprElem *NestedOrFunctionCall::nud() { 
    ParseResult prExpr = p->parseExpr( 0 ) ;
    Expr *exp = dynamic_cast<Expr *>(prExpr.ast);

    pr.ast = new ParenExpr( exp );
    p->match(rightParen) ;
    return this ; 
}

// LetExpr
// Expr ::= 'let' Stmts 'in' Expr 'end'
LetExpr::LetExpr ( Parser *_p ) : ExprElem ( _p ) { }
ExprElem *LetExpr::nud() {
    ParseResult prStmts = p->parseStmts() ;
    Statements *ss = dynamic_cast<Statements *>(prStmts.ast);
    p->match(inKwd) ;
    ParseResult PrExpr = p->parseExpr(0) ;
    Expr *e1 = dynamic_cast<Expr *>(PrExpr.ast);
    p->match(endKwd);

    pr.ast = new LetExprObject( ss, e1 );

    return this ;
}


// IfExpr
// Expr ::= 'if' Expr 'then' Expr 'else' Expr
IfExpr::IfExpr ( Parser *_p ) : ExprElem ( _p ) { }
ExprElem *IfExpr::nud() {
    ParseResult prExp1 = p->parseExpr(0) ;
    Expr *e1 = dynamic_cast<Expr *>(prExp1.ast);
    p->match(thenKwd) ;
    ParseResult prExp2 = p->parseExpr(0) ;
    Expr *e2 = dynamic_cast<Expr *>(prExp2.ast);
    p->match(elseKwd);
    ParseResult prExp3 = p->parseExpr(0) ;
    Expr *e3 = dynamic_cast<Expr *>(prExp3.ast);

    pr.ast = new IfExprObject( e1, e2, e3 );
    return this ;
}

// NotExpr
// Expr ::= '!' Expr
NotExpr::NotExpr ( Parser *_p ) : ExprElem ( _p ) { }
ExprElem *NotExpr::nud() {
    ParseResult prExpr = p->parseExpr(0) ;
    Expr *e1 = dynamic_cast<Expr *>(prExpr.ast);
    pr.ast = new NotExprObject( e1 );
    return this ;
}


/* This function defines the "left-binding-power" of the different
   operators.  This represents, essentially, their precedence in
   relation to other operators - higher values indicate higher
   precedence.
*/
int lbp(tokenType tt) {
    switch (tt) {
    case varName: 
    case integerConst: case floatConst: 
    case stringConst: case booleanConst: 
        return 0 ;

    case semiColon: case comma:
    case rightSquare: case rightParen: case rightCurly:
        return 0 ;

    // Logical operators
    case andOp: case orOp:
        return 30 ;
    // Relational Operators
    case equalTo: case notEqualTo:
    case lessThan: case lessThanEqual:
    case greaterThan: case greaterThanEqual:
        return 40 ;
    // Arithemetic
    case add: case subtract: 
        return 50 ;
    case multiply: case divide:
        return 60 ;

    case leftSquare: case leftParen:
        return 80 ;

    default: return 0 ;
    }
}



// Helper function used by the parser.

void Parser::match (tokenType tt) {
    if (! attemptMatch(tt)) {
        printf("bad match attempt\n");
        printf("lex: %s - %s\n", getTokenTypeName(tt), getTokenTypeName(currToken->terminal));
        throw ( makeErrorMsg ( tt ) ) ;
    }
}

bool Parser::attemptMatch (tokenType tt) {
    if (currToken->terminal == tt) { 
        nextToken() ;
        return true ;
    }
    return false ;
}

bool Parser::nextIs (tokenType tt) {
    return currToken->terminal == tt ;
}

void Parser::nextToken () {
    if (currToken->next == NULL)
        throw ( makeErrorMsg ( endOfFile ) ) ;
    else {
        prevToken = currToken ;
        currToken = currToken->next ;
    }
}


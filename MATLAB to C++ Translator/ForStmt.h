#ifndef ForStmt_H
#define ForStmt_H

#include "Statement.h"
#include <string>
#include "Debug.h"

using namespace std;

class ForStmt : public Statement {
    public:
        ForStmt (VarName *v, Expr *e1, Expr *e2, Statement *s) : var( v ), ex1 ( e1 ), ex2 ( e2 ), st( s ) { outLog("Calling ForStmt Constructor\n"); }
        virtual ~ForStmt() { outLog("calling ForStmt deconstructor\n"); delete var; delete ex1; delete ex2; delete st; }

        VarName *var;
        Expr *ex1;
        Expr *ex2;
        Statement *st;

        string unparse() {
            outLog("calling unparse on forStmt\n");
            return "for (" + var->unparse() + " = " + ex1->unparse() + " to " + ex2->unparse() + ")\n" + st->unparse();
        }

        string cppCode() {
            outLog("calling cppCode on forStmt\n");
            return "for (" + var->cppCode() + " = " + ex1->cppCode() + " ; " + var->cppCode() + " <= " + ex2->cppCode() + " ; " + var->cppCode() + "++) " + st->cppCode();
        }
} ;

#endif // ForStmt_H

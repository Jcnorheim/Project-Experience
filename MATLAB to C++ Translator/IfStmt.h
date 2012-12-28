#ifndef IfStmt_H
#define IfStmt_H

#include "Statement.h"
#include <string>
#include "Debug.h"

using namespace std;

class IfStmt : public Statement {
    public:
        IfStmt (Expr *c, Statement *t, Statement *e) : condition( c ), then ( t ), els ( e ) { outLog("Calling IfStmt Constructor (else)\n"); }
        IfStmt (Expr *c, Statement *t) : condition ( c ), then ( t ) { outLog("Calling IfStmt Constructor\n"); }
        virtual ~IfStmt() { outLog("calling IfStmt deconstructor\n"); delete condition; delete then; delete els; }

        Expr* condition;
        Statement* then;
        Statement* els;

        string unparse() {
            outLog("calling unparse on IfStmt\n");
            string E = "";
            if (els != NULL) {
                E = "else\n" + els->unparse();
            }
            return "if (" + condition->unparse() + ")\n" + then->unparse() + E;
        }

        string cppCode() {
            outLog("calling cppCode on IfStmt\n");
            string E = "";
            if (els != NULL) {
                E = "else " + els->cppCode();
            }
            return "if (" + condition->cppCode() + ")\n    " + then->cppCode() + E;

        }
} ;

#endif // IfStmt_H

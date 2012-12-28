#ifndef PrintStmt_H
#define PrintStmt_H

#include "Statement.h"
#include <string>
#include "Debug.h"

using namespace std;

class PrintStmt : public Statement {
    public:
        PrintStmt (Expr *e) : ex ( e ) { outLog("Calling PrintStmt Constructor\n"); }
        virtual ~PrintStmt() { outLog("Calling PrintStmt deconstructor\n"); delete ex; }

        Expr* ex;

        string unparse() {
            return "print(" + ex->unparse() + ");\n";
        }

        string cppCode() {
            return "cout << " + ex->cppCode() + ";\n";
        }
} ;

#endif // PrintStmt_H

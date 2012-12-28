#ifndef Assignment_H
#define Assignment_H

#include "Statement.h"
#include <string>
#include "VarName.h"
#include "Debug.h"

class Assignment : public Statement {
    public:
        Assignment () {}
        Assignment (LExpr *v, Expr *e) : var(v), exp(e) { outLog("calling Assignment constructor\n"); }
        virtual ~Assignment() { outLog("calling Assignment deconstructor\n"); delete var; delete exp; }

        LExpr *var;
        Expr *exp;

        std::string unparse() {
            outLog("Calling unparse on Assignment\n");
            return var->unparse() + " = " + exp->unparse() + ";\n";
        }

        std::string cppCode() {
            outLog("Calling cppCode on Assignment\n");
            std::string r = var->cppCode() + " = ";
            r += exp->cppCode() + ";\n";
            return r;
        }
} ;

#endif // Assignment_H

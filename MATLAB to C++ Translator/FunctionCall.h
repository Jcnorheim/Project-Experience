#ifndef FunctionCall_H
#define FunctionCall_H

#include "Expr.h"
#include <string>
#include "scanner.h"
#include "Debug.h"

class FunctionCall : public Expr {
    public:
        FunctionCall(VarName *v, Expr *e1) : var( v ), exp( e1 ) { outLog("calling FunctionCall constructor\n"); }

        VarName *var;
        Expr *exp;

        virtual ~FunctionCall(){ outLog("Calling FunctionCall deconstructor\n"); delete var; delete exp; }

        std::string unparse() {
            outLog("calling unparse on FunctionCall()\n");
		    return var->unparse() + "(" + exp->unparse() + ")";
	    }

        std::string cppCode() {
            outLog("calling cppCode on FunctionCall()\n");
            std::string v = var->cppCode();
            std::string e = exp->cppCode();
            outLog("var: ");
            outLog(v.c_str());
            outLog("\n");
            outLog("exp: ");
            outLog(e.c_str());
            outLog("\n");
            outLog("past\n");
            if (v.compare("readMatrix") == 0) {
                outLog("here first\n");
                return "Matrix::" + var->cppCode() + "(" + exp->cppCode() + ")";
            }
            else if ((v.compare("numRows") == 0) or (v.compare("numCols") == 0)) {
                outLog("here!\n");
                return exp->cppCode() + "." + var->cppCode() + "()";
            } else {
                return v + "(" + e + ")" + "\n";
            }
        }
} ;

#endif // FunctionCall_H


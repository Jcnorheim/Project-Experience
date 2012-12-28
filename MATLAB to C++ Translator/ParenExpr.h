#ifndef ParenExpr_H
#define ParenExpr_H

#include "Expr.h"
#include <string>
#include "scanner.h"
#include "Debug.h"

class ParenExpr : public Expr {
    public:
        ParenExpr(Expr *e1) : exp( e1 ) { outLog("calling ParenExpr constructor\n"); }

        Expr *exp;

        virtual ~ParenExpr(){ outLog("Calling ParenExpr deconstructor\n"); delete exp; }

        std::string unparse() {
            outLog("calling unparse on ParenExpr()\n");
		    return "(" + exp->unparse() + ")";
	    }

        std::string cppCode() {
            outLog("calling cppCode on ParenExpr()\n");
            return "(" + exp->cppCode() + ")";
        }
} ;

#endif // ParenExpr_H


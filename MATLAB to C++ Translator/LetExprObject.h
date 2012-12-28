#ifndef LetExprObject_H
#define LetExprObject_H

#include "Expr.h"
#include <string>
#include "Debug.h"

class LetExprObject : public Expr {
    public:
        LetExprObject(Statements *s, Expr *e1) : ss( s ), exp( e1 ) { outLog("calling LetExprObject constructor\n"); }

        Statements *ss;
        Expr *exp;

        virtual ~LetExprObject(){ outLog("Calling LetExprObject deconstructor\n"); delete exp; delete ss; }

        std::string unparse() {
            outLog("calling unparse on LetExprObject()\n");
		    return "let\n" + ss->unparse() + "in\n" +exp->unparse() + "\nend";
	    }

        std::string cppCode() {
            outLog("calling cppCode on LetExprObject()\n");
            return "({\n" + ss->cppCode() + "    " + exp->cppCode() + "; })";
        }
} ;

#endif // LetExprObject_H


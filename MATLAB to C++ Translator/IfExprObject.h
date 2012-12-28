#ifndef IfExprObject_H
#define IfExprObject_H

#include "Expr.h"
#include <string>
#include "Debug.h"

class IfExprObject : public Expr {
    public:
        IfExprObject(Expr *e1, Expr *e2, Expr *e3) : exp1( e1 ), exp2( e2 ), exp3 ( e3 ) { outLog("calling IfExprObject constructor\n"); }

        Expr *exp1;
        Expr *exp2;
        Expr *exp3;

        virtual ~IfExprObject(){ outLog("Calling IfExprObject deconstructor\n"); delete exp1; delete exp2; delete exp3; }

        std::string unparse() {
            outLog("calling unparse on IfExprObject()\n");
		    return "if " + exp1->unparse() + "\nthen " + exp2->unparse() + "\nelse " + exp3->unparse();
	    }

        std::string cppCode() {
            outLog("calling cppCode on IfExprObject()\n");
            return exp1->cppCode() + " ? " + exp2->cppCode() + " : " + exp3->cppCode();
        }
} ;

#endif // IfExprObject_H


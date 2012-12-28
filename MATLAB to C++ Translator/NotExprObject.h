#ifndef NotExprObject_H
#define NotExprObject_H

#include "Expr.h"
#include <string>
#include "Debug.h"

class NotExprObject : public Expr {
    public:
        NotExprObject(Expr *e1) : exp( e1 ) { outLog("calling NotExprObject constructor\n"); }

        Expr *exp;

        virtual ~NotExprObject(){ outLog("Calling NotExprObject deconstructor\n"); delete exp; }

        std::string unparse() {
            outLog("calling unparse on NotExprObject()\n");
		    return "! " + exp->unparse();
	    }
} ;

#endif // NotExprObject_H


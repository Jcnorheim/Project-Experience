#ifndef MatrixRefObject_H
#define MatrixRefObject_H

#include "Expr.h"
#include <string>
#include "Debug.h"

class MatrixRefObject : public LExpr {
    public:
        MatrixRefObject(VarName *vn, Expr *e1, Expr *e2) : var( vn ), e1( e1 ), e2( e2 ) { outLog("calling MatrixRefObject constructor\n"); }

        VarName *var;
        Expr *e1;
        Expr *e2;

        virtual ~MatrixRefObject(){ outLog("Calling MatrixRefObject deconstructor\n"); delete var; delete e1; delete e2; }

        std::string unparse() {
            outLog("calling unparse on MatrixRefObject()\n");
		    return var->unparse() + " [ " + e1->unparse() + " , " + e2->unparse() + " ] ";
	    }

        std::string cppCode() {
            outLog("calling cppCode on MatrixRefObject()\n");
		    return "*(" + var->cppCode() + ".access( " + e1->unparse() + " , " + e2->unparse() + " )) ";
	    }
} ;

#endif // MatrixRefObject_H


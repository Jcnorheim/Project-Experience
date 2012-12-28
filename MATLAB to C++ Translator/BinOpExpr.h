#ifndef BinOpExpr_H
#define BinOpExpr_H

#include "Expr.h"
#include <string>
#include "Debug.h"

class BinOpExpr : public Expr {
    public:
        BinOpExpr (Expr *l, std::string *s, Expr *r) : left( l ), op( s ), right( r ){ outLog("Calling BinOpExpr constructor\n"); }
        virtual ~BinOpExpr() { outLog("Calling BinOpExpr constructor\n"); delete left; delete op; delete right; }

        Expr *left;
        std::string *op;
        Expr *right;

        std::string unparse() {
            outLog("Calling unparse on BinOpExpr\n");
            return left->unparse() + " " + *op + " " + right->unparse();
        }

        std::string cppCode() {
            outLog("Calling cppCode on BinOpExpr\n");
            return "(" + left->cppCode() + " " + *op + " " + right->cppCode() + ")";
        }
} ;

#endif // BinOpExpr_H

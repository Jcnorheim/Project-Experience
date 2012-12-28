#ifndef MatrixDecl_H
#define MatrixDecl_H

#include "Statement.h"
#include <string>
#include "VarName.h"
#include "Debug.h"

using namespace std;

class MatrixDecl : public Statement {
    public:
        MatrixDecl (VarName *v, Expr *e1, Expr *e2, VarName *vn1, VarName *vn2, Expr *e3) : name (v), exp1(e1), exp2(e2),
                                                                        v0 (vn1), v1 (vn2), exp3 (e3) { outLog("Calling MatrixDecl Constructor\n"); }
        MatrixDecl (VarName *v, Expr *e1) : name (v), exp1 (e1) { }
        virtual ~MatrixDecl() { outLog("Calling MatrixDecl deconstructor\n"); delete name; delete exp1; delete exp2; delete v0; delete v1; delete exp3; }

        VarName *name;
        Expr *exp1;
        Expr *exp2;
        VarName *v0;
        VarName *v1;
        Expr *exp3;

        string unparse() {
            outLog("calling unparse on MatrixDecl\n");
            if (exp2 != NULL) {
                return "Matrix " + name->unparse() + "[ " + exp1->unparse() + " , " + exp2->unparse() + "] " + v0->unparse() + " , " + v1->unparse() + " = " + exp3->unparse() + ";\n";
            }
            else {
                return "Matrix " + name->unparse() + " = " + exp1->unparse() + ";\n";
            }
        }

        string cppCode() {
            outLog("calling cppCode on MatrixDecl\n");
            if (exp2 != NULL) {
            string r = "Matrix " + name->cppCode() + "( " + exp1->cppCode() + ", " + exp2->cppCode() + ");\nfor (int " + v0->cppCode() + " = 0; " + v0->cppCode() + " < " + exp1->cppCode() + "; " + v0->cppCode() + "++) {\n";
                r += "    for (int " + v1->cppCode() + " = 0; " + v1->cppCode() + " < " + exp2->cppCode() + "; " + v1->cppCode() + "++ ) {\n";
                r += "        *(" + name->cppCode() + ".access(" + v0->cppCode() + ", " + v1->cppCode() + ")) = " + exp3->cppCode() + ";\n";
                r += "    }\n}\n";
                return r;
            }
            else {
                return "Matrix " + name->cppCode() + " = " + exp1->cppCode() + ";\n";
            }
        }
} ;

#endif // MatrixDecl_H

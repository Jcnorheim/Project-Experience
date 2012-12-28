#ifndef Declaration_H
#define Declaration_H

#include "Statement.h"
#include <string>
#include "VarName.h"
#include "Debug.h"
#include "Conversion.h"

using namespace std;

class Declaration : public Statement {
    public:
        Declaration (string *t, VarName *v) : Type(t), var(v) { outLog("Calling Declaration Constructor\n"); }
        virtual ~Declaration() { outLog("Calling Declaration deconstructor\n"); delete Type; delete var; }

        string *Type;
        VarName *var;

        string unparse() {
            outLog("Calling unparse on Declaration\n");
            return *Type + " " + var->unparse() + ";\n";
        }

        string cppCode() {
            outLog("Calling cppCode on Declaration\n");
            return cppType(*Type) + " " + var->cppCode() + ";\n";
        }
} ;

#endif // Declaration_H

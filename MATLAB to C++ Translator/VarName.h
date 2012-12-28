#ifndef VarName_H
#define VarName_H

#include "LExpr.h"
#include <string>
#include "scanner.h"
#include "Debug.h"

class VarName : public LExpr {
    public:
        VarName() { }
        VarName(std::string *n) : name( n ) { outLog("calling VarName constructor\n"); }

        std::string *name;

        virtual ~VarName(){ outLog("Calling VarName deconstructor\n"); delete name; }

        std::string unparse() {
            outLog("calling unparse on Varname()\n");
		    return *name;
	    }

        std::string cppCode() {
            outLog("calling cppCode on Varname()\n");
            return *name;
        }
} ;

#endif // VarName_H


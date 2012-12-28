#ifndef AnyConst_H
#define AnyConst_H

#include "Expr.h"
#include <string>
#include "Debug.h"

class AnyConst : public Expr {
    public:
        AnyConst (std::string *d) : data( d ) { outLog("calling AnyConst constructor\n"); }
        virtual ~AnyConst() { outLog("calling AnyConst deconstructor\n"); delete data; }

        std::string *data;

        std::string unparse() {
            outLog("calling unparse on AnyConst()\n");
            return *data;
        }

        std::string cppCode() {
            outLog("calling cppCode on AnyConst()\n");
            return *data;
        }
} ;

#endif // AnyConst_H

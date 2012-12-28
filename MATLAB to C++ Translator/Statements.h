#ifndef Statements_H
#define Statements_H

#include "Statement.h"
#include <string>
#include "scanner.h"

class Statements : public Statement{
    public:
        Statements() {}
        Statements(Statement* s, Statements* ss) : R( s ), N ( ss ) { }

        Statement *R;
        Statements *N;

        virtual ~Statements() {outLog("calling Statements deconstructor\n"); delete R; delete N;}

        std::string unparse() {
            outLog("calling unparse on Statements\n");
            if (R == NULL) {
                return "";
            }
            return R->unparse() + N->unparse();
        }

        std::string cppCode() {
            outLog("calling cppCode on Statements\n");
            if (R == NULL) {
                return "";
            }
            return "    " + R->cppCode() + N->cppCode();
        }
} ;

#endif // Statements_H

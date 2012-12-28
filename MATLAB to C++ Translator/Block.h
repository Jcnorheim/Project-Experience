#ifndef block_H
#define block_H

#include "scanner.h"
#include "Statements.h"
#include <string>

class Block : public Statements {
    public:
        Block(Statements *ss) : sl( ss ) { outLog("calling Block Constructor\n"); }

        Statements *sl;

        virtual ~Block(){ outLog("calling Block deconstructor\n"); delete sl; }

        std::string unparse() {
            return "{\n" + sl->unparse() + "}\n";
        }

        std::string cppCode() {
            return "{\n" + sl->cppCode() + "}\n";
        }
} ;

#endif // block_H

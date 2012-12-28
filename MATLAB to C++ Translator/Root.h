#ifndef Root_H
#define Root_H

#include "Node.h"
#include <string>
#include "scanner.h"
#include "Debug.h"
#include <stdio.h>

class Root : public Node {
    public:
        Root() { }
        Root(Node *e1, Node *e2) : R( e1 ), N( e2 ) { outLog("calling Root's constructor\n"); }

        Node* R;
        Node* N;

        virtual ~Root() { outLog("calling Root's deconstructor\n"); delete R; delete N; } ;
        virtual std::string unparse() {
            outLog("calling unparse on Root\n");
            return R->unparse() + "() {\n" + N->unparse() + "}";
        }

        virtual std::string cppCode() {
            outLog("calling cppCode on Root\n");
            return "#include <iostream>\n#include \"Matrix.h\"\n#include <math.h>\n\nusing namespace std;\n\nint " + R->cppCode() + "() {\n" + N->cppCode() + "}";
        }
} ;

#endif // Root_H

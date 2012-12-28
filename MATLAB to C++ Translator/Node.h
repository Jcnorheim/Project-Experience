#ifndef NODE_H
#define NODE_H
#include <string>
class Node {
    public:
        Node() { }
        virtual ~Node()  { }
        virtual std::string cppCode() {
            return "";
        }
        virtual std::string unparse() {
            return "";
        }
} ;

#endif // NODE_H


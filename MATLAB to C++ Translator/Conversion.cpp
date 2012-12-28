#include <string>

std::string cppType(std::string mt) {
    if (mt.compare("Integer") == 0) {
        return "int";
    }
    else if (mt.compare("Boolean") == 0) {
        return "bool";
    }
    else if (mt.compare("Float") == 0) {
        return "float";
    }
    else {
        return "Error";
    }
}

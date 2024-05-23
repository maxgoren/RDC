#ifndef repl_hpp
#define repl_hpp
#include <iostream>
#include <cmath>
#include <unordered_map>
#include "astbuilder.hpp"
using namespace std;

class REPL {
    private:
        ASTBuilder astBuilder;
        unordered_map<string, double> env;
        bool tracing;
        double eval(ASTNode* node);
        double expr(ASTNode* node);
    public:
        REPL();
        void repl();
};

#endif
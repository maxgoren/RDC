#ifndef astbuilder_hpp
#define astbuilder_hpp
#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
using std::string;

class ASTBuilder {
    private:
        Lexer lexer;
    public:
        ASTBuilder();
        ASTNode* build(string text);
};

#endif
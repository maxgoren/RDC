#ifndef ast_hpp
#define ast_hpp
#include "lexer.hpp"
#include <iostream>
using std::string;

enum ExprK {ID_EXPR, OP_EXPR, UOP_EXPR, CONST_EXPR};

struct ASTNode {
    ExprK type;
    struct { TOKENS tokenVal; string stringVal; double doubleVal; } data;
    ASTNode* next;
    ASTNode* left;
    ASTNode* right;
};

ASTNode* makeExprNode(ExprK type, TOKENS token, string str);

inline int rd = 0;
void show(ASTNode* node);

#endif
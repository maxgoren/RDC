#ifndef parser_hpp
#define parser_hpp
#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "ast.hpp"
using namespace std;


class Parser {
    private:
        vector<Lexeme> lexemes;
        int lexPos;
        Lexeme current;
        TOKENS lookahead();
        void nexttoken();
        void prevtoken();
        bool match(TOKENS token);
    public:
        Parser();
        ASTNode* parse(vector<Lexeme>& tokens);
    public:
        ASTNode* program();
        ASTNode* simpleExpr();
        ASTNode* expr();
        ASTNode* term();
        ASTNode* factor();
        ASTNode* primary();
};

#endif
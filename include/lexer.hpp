#ifndef lexer_hpp
#define lexer_hpp
#include "buffer.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

enum TOKENS {
    ERROR, WHITESPACE, EOFTOKEN,
    NUMBER, ID,
    PLUS, MINUS, MULTIPLY, DIVIDE, MOD, POW,
    ASSIGN, SEMI, COLON, PERIOD, COMA, NOT,
    LPAREN, RPAREN,
    LESS, GREATER, EQUAL, NOTEQUAL, LTE, GTE
};

inline string tokenString[] = {
    "ERROR", "WHITESPACE", "EOFTOKEN",
    "NUMBER", "ID",
    "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD", "POW",
    "ASSIGN", "SEMI", "COLON", "PERIOD", "COMA", "NOT",
    "LPAREN", "RPAREN", 
    "LESS", "GREATER", "EQUAL", "NOTEQUAL", "LTE", "GTE"
};

struct Lexeme {
    TOKENS tokenVal;
    string stringVal;
    int lineNumber;
    Lexeme(TOKENS t = ID, string sv = "(empty)", int ln = 0) {
        tokenVal = t;
        stringVal = sv;
        lineNumber = ln;
    }
};

class Lexer {
    private:
        Buffer sb;
        stack<char> parStack;
        vector<Lexeme> lexemes;
        Lexeme extractWord();
        Lexeme extractNumber();
        Lexeme checkSpecials();
        vector<Lexeme>& start();
    public:
        Lexer();
        vector<Lexeme>& lexString(string str);
};

#endif
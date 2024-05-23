#include "./include/parser.hpp"

TOKENS Parser::lookahead() {
    return current.tokenVal;
}

void Parser::nexttoken() {
    if (lexPos+1 == lexemes.size()) {
        current = Lexeme(EOFTOKEN, "<fin>", lexPos);
    } else {
        current = lexemes[++lexPos];
    }
}

void Parser::prevtoken() {
    current = lexemes[--lexPos];
}

bool Parser::match(TOKENS token) {
    if (token == current.tokenVal) {
        nexttoken();
        return true;
    }
    if (current.tokenVal != EOFTOKEN) {
        cout<<"mismatched token on line "<<current.lineNumber<<": "<<tokenString[current.tokenVal]<<", near: "<<current.stringVal<<", expected: "<<tokenString[token]<<endl;
    }
    return false;
}

Parser::Parser() {


}

ASTNode* Parser::parse(vector<Lexeme>& tokens) {
    lexemes = tokens;
    current = tokens[0];
    if (tokens[0].tokenVal == EOFTOKEN)
        return nullptr;
    lexPos = 0;
    return program();
}

ASTNode* Parser::program() {
    ASTNode* node = nullptr;
    node = simpleExpr();
    return node;
}

ASTNode* Parser::simpleExpr() {
    ASTNode* node = expr();
    while (lookahead() == LESS || lookahead() == EQUAL || lookahead() == LTE ||
           lookahead() == GTE || lookahead() == GREATER || lookahead() == NOTEQUAL) {
        ASTNode* t = makeExprNode(OP_EXPR, lookahead(), current.stringVal);
        t->left = node;
        node = t;
        match(lookahead());
        node->right = expr();
    }
    return node;
}

ASTNode* Parser::expr() {
    ASTNode* node = term();
    while (lookahead() == PLUS || lookahead() == MINUS) {
        ASTNode* t = makeExprNode(OP_EXPR, lookahead(), current.stringVal);
        t->left = node;
        node = t;
        match(lookahead());
        node->right = term();
    }
    return node;
}

ASTNode* Parser::term() {
    ASTNode* node = factor();
    while (lookahead() == MULTIPLY || lookahead() == DIVIDE) {
        ASTNode* t = makeExprNode(OP_EXPR, lookahead(), current.stringVal);
        t->left = node;
        node = t;
        match(lookahead());
        node->right = factor();
    }
    return node;
}

ASTNode* Parser::factor() {
    ASTNode* node = primary();
    while (lookahead() == POW) {
        ASTNode* t = makeExprNode(OP_EXPR, lookahead(), current.stringVal);
        t->left = node;
        node = t;
        match(POW);
        node->right = primary();
    }
    return node;
}

ASTNode* Parser::primary() {
    ASTNode* node = nullptr;
    switch (lookahead()) {
        case MINUS:
            node =  makeExprNode(UOP_EXPR, MINUS, current.stringVal);
            match(MINUS);
            node->left = primary();
            break;
        case ID:
            node = makeExprNode(ID_EXPR, ID, current.stringVal);
            match(ID);
            if (lookahead() == ASSIGN) {
                ASTNode* t = makeExprNode(OP_EXPR, lookahead(), current.stringVal);
                t->left = node;
                node = t;
                match(ASSIGN);
                node->right = expr();
                return node;
            }
            break;
        case NUMBER:
            node = makeExprNode(CONST_EXPR, NUMBER, current.stringVal);
            match(NUMBER);
            break;
        case LPAREN:
            match(LPAREN);
            node = expr();
            match(RPAREN);
            break;
        default:
            cout<<"Ruh roh rhaggy"<<endl;
    }
    return node;
}



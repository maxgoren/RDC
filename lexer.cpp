#include "./include/lexer.hpp"

Lexeme Lexer::extractWord() {
    string word;
    while (sb.getChar() != sb.EOFMark() && isalnum(sb.getChar())) {
        word.push_back(sb.getChar());
        sb.nextChar();
    }
    sb.unGet();
    return Lexeme(ID, word, sb.lineNumber());
}

Lexeme Lexer::extractNumber() {
    string word;
    while (sb.getChar() != sb.EOFMark() && (isdigit(sb.getChar()) || sb.getChar() == '.')) {
        word.push_back(sb.getChar());
        sb.nextChar();
    }
    sb.unGet();
    return Lexeme(NUMBER, word, sb.lineNumber());
}

Lexeme Lexer::checkSpecials() {
    if (sb.getChar() == ' ' || sb.getChar() == '\t' || sb.getChar() == '\r' || sb.getChar() == '\n') 
        return Lexeme(WHITESPACE, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '(') { parStack.push(sb.getChar()); return Lexeme(LPAREN, sb.asString(), sb.lineNumber()); }
    if (sb.getChar() == ')') {  
        if (parStack.top() != '(') {
            cout<<"Error: Mismatched Parentheses on line "<<sb.lineNumber()<<endl;
            return Lexeme(ERROR, "<error>", sb.lineNumber());
        } else {
            parStack.pop();
        }   
        return Lexeme(RPAREN, sb.asString(), sb.lineNumber()); 
    }
    if (sb.getChar() == '+') return Lexeme(PLUS, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '-') return Lexeme(MINUS, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '/') return Lexeme(DIVIDE, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '*') return Lexeme(MULTIPLY, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '%') return Lexeme(MOD, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '^') return Lexeme(POW, sb.asString(), sb.lineNumber());
    if (sb.getChar() == ';') return Lexeme(SEMI, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '.') return Lexeme(PERIOD, sb.asString(), sb.lineNumber());
    if (sb.getChar() == ',') return Lexeme(COMA, sb.asString(), sb.lineNumber());
    if (sb.getChar() == '<') {
        sb.nextChar();
        if (sb.getChar() == '=') 
            return Lexeme(LTE, "<=", sb.lineNumber());
        sb.unGet();
        return Lexeme(LESS, sb.asString(), sb.lineNumber()); }
    if (sb.getChar() == '>') {
        sb.nextChar();
        if (sb.getChar() == '=') 
            return Lexeme(GTE, "==", sb.lineNumber());
        sb.unGet();
        return Lexeme(GREATER, sb.asString(), sb.lineNumber());
    }
    if (sb.getChar() == '!') {
        sb.nextChar();
        if (sb.getChar() == '=') 
            return Lexeme(NOTEQUAL, "==", sb.lineNumber());
        sb.unGet();
         return Lexeme(NOT, "!", sb.lineNumber());
    }
    if (sb.getChar() == '=') {
        sb.nextChar();
        if (sb.getChar() == '=') 
            return Lexeme(EQUAL, "==", sb.lineNumber());
        sb.unGet();
         return Lexeme(ERROR, "<error>", sb.lineNumber());
    }
    if (sb.getChar() == ':') {
        sb.nextChar();
        if (sb.getChar() == '=') {
            return Lexeme(ASSIGN, ":=", sb.lineNumber());
        }
        sb.unGet();
        return Lexeme(COLON, sb.asString(), sb.lineNumber());
    }
    cout<<"No idea what a "<<sb.getChar()<<" is"<<endl;
    return Lexeme(ERROR, "<error>", sb.lineNumber());
}

Lexer::Lexer() {

}

vector<Lexeme>& Lexer::lexString(string str) {
    sb.load(str);
    return start();
}

vector<Lexeme>& Lexer::start() {
    Lexeme next;
    lexemes.clear();
    if (!parStack.empty()) {
        while (!parStack.empty()) parStack.pop();
    }
    while (sb.getChar() != sb.EOFMark()) {
        if (isalpha(sb.getChar())) {
            next = extractWord();
        } else if (isdigit(sb.getChar())) {
            next = extractNumber();
        } else {
            next = checkSpecials();
        }
        if (next.tokenVal != WHITESPACE)
            lexemes.push_back(next);
        if (lexemes.back().tokenVal == ERROR) {
            cout<<"Error encountered, aborting."<<endl;
            lexemes.clear();
            break;
        }
        if (sb.getChar() == sb.EOFMark())
            break;
        sb.nextChar();
    }
    if (!parStack.empty()) {
        cout<<"Error: Missing ";
        switch (parStack.top()) {
            case '{': cout<<"}!"<<endl;
                break;
            case '(': cout<<")!"<<endl;
                break;
            case '[': cout<<"]!"<<endl;
                break;
            default:
                cout<<" paren"<<endl;
                break;
        }
        lexemes.clear();
    }
    lexemes.push_back(Lexeme(EOFTOKEN, "<EOF>", sb.lineNumber()));
    return lexemes;
}
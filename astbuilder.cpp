#include "./include/astbuilder.hpp"

ASTBuilder::ASTBuilder() {

}

ASTNode* ASTBuilder::build(string text) {
    Parser parser;
    auto tokens = lexer.lexString(text);
    for (auto m : tokens) {
        cout<<m.lineNumber<<": "<<tokenString[m.tokenVal]<<", "<<m.stringVal<<endl;
    }
    return parser.parse(tokens);
}
#include "./include/repl.hpp"

REPL::REPL() {
    tracing = false;
}

double REPL::expr(ASTNode* node) {
    if (node != nullptr) {
        switch(node->type) {
            case OP_EXPR:
                return eval(node);
            case UOP_EXPR:
                return -(stod(node->left->data.stringVal.c_str()));
            case CONST_EXPR:
                return stod(node->data.stringVal.c_str());
            case ID_EXPR:
                return env[node->data.stringVal];
        }
    }
    return 0;
}

double REPL::eval(ASTNode* node) {
    if (node != nullptr) {
        double left = expr(node->left);
        double right = expr(node->right);
        switch (node->data.tokenVal) {
            case PLUS: return left + right;
            case MINUS: return left - right;
            case MULTIPLY: return left * right;
            case DIVIDE:
                if (right == 0) {
                    cout<<"Error: divide by zero"<<endl;
                    return 0;
                }
                return left / right;
            case POW:      return pow(left, right);
            case LESS:     return left < right;
            case GREATER:  return left > right;
            case LTE:      return  left <= right;
            case GTE:      return left >= right;
            case EQUAL:    return left == right;
            case NOTEQUAL: return left != right;
            case ASSIGN:
                env[node->left->data.stringVal] = right;
                cout<<"Binding: "<<node->left->data.stringVal<<" to "<<right<<endl;
                return left;
            default:
                break;
        }
    }
    return 0;
}

void REPL::repl() {
    string input;
    while (input != ".exit" && input != "quit") {
        cout<<"Calc> ";
        getline(cin, input);
        cout<<"   '-> "<<input<<endl;
        if (input != ".exit" && input != "quit") {
            auto ast = astBuilder.build(input);
            rd = 0;
            show(ast);
            cout<<expr(ast)<<endl;
        }
    }
}
#include "./include/ast.hpp"

ASTNode* makeExprNode(ExprK type, TOKENS token, string str) {
    ASTNode* node = new ASTNode;
    node->type = type;
    node->data.stringVal = str;
    node->data.tokenVal = token;
    node->left = nullptr;
    node->right = nullptr;
    node->next = nullptr;
    return node;
}

void say(string s) {    
    for (int i = 0; i < rd; i++) cout<<"  ";
    cout<<s;
}

bool isLeaf(ASTNode* node) {
    if (node == nullptr)
        return true;
    return (node->left == nullptr && node->right == nullptr);
}

void show(ASTNode* node) {
    rd++;      
    if (node != nullptr) {
        say("(");  
        say(tokenString[node->data.tokenVal] +": " + node->data.stringVal + (isLeaf(node) ? " ":"\n"));
        show(node->left);
        show(node->right);
        say(")\n");
    }
    rd--;
}
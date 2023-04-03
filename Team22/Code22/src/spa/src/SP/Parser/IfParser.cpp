//
// Created by Yi Zhang on 3/4/23.
//
#include "IfParser.h"

std::shared_ptr<TreeNode> IfParser::parse() {
    TNode ifNode;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "if")) {
        cout << "Expected 'if' keyword but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ifNode.nodeType = TokenType::IF;
    ifNode.stringId = tokenList[pos].value;
    ifNode.stmtNumber = tokenList[pos].lineNumber;
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
        cout << "Expected '(' after 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode condChild = parseConditionalExpr();
    if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        cout << "Expected ')' after cond_expr of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "then")) {
        cout << "Expected 'then' keyword after (cond_expr) of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expected '{' keyword after 'then' keyword of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode thenBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' keyword after stmtList of 'then' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "else")) {
        cout << "Expected 'else' keyword after '}' of 'then' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expected '{' keyword after 'else' keyword of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode elseBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' keyword after stmtList of 'else' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    ifNode.children.push_back(condChild);
    ifNode.children.push_back(thenBody);
    ifNode.children.push_back(elseBody);
    return ifNode;
}

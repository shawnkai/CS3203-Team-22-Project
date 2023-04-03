
#include "WhileParser.h"

TreeNode WhileParser::parse() {
    Token currToken = tokenList[pos];
    TNode whileNode;
    whileNode.nodeType = currToken.type;
    whileNode.stringId = currToken.value;
    whileNode.stmtNumber = currToken.lineNumber;
    if (currToken.type != TokenType::WHILE) {
        cout << "Expected 'while' keyword for the statement but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token next = tokenList[++ pos];
    if (next.type != TokenType::LEFT_ROUND_BRACKET) {
        cout << "Expected '(' after while keyword but instead got: " << next.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode condChild = parseConditionalExpr();
    if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        cout << "Expected ')' after conditional expr in 'while' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }

    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expected '{' after conditional expr in 'while' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode whileBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' after stmtList in 'while' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    whileNode.children.push_back(condChild);
    whileNode.children.push_back(whileBody);
    return whileNode;
}
//
// Created by Yi Zhang on 3/4/23.
//
#include "IfParser.h"

TNode IfParser::parse() {
    TNode ifNode;
    if (!(tokenList[*pos].type == TokenType::IF && tokenList[*pos].value == "if")) {
        std::cout << "Expected 'if' keyword but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ifNode.nodeType = TokenType::IF;
    ifNode.stringId = tokenList[*pos].value;
    ifNode.stmtNumber = tokenList[*pos].lineNumber;
    ++*pos;
    if (tokenList[*pos].type != TokenType::LEFT_ROUND_BRACKET) {
        std::cout << "Expected '(' after 'if' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    ParserFactory factory;
    auto condChild = factory.createParser(CONDITIONAL_EXPR, tokenList, pos)->parse();
    if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        std::cout << "Expected ')' after cond_expr of 'if' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    if (!(tokenList[*pos].type == TokenType::IF && tokenList[*pos].value == "then")) {
        std::cout << "Expected 'then' keyword after (cond_expr) of 'if' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    if (tokenList[*pos].type != TokenType::LEFT_CURLY_BRACKET) {
        std::cout << "Expected '{' keyword after 'then' keyword of 'if' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    auto thenBody = factory.createParser(STATEMENT_LIST, tokenList, pos)->parse();
    if (tokenList[*pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        std::cout << "Expected '}' keyword after stmtList of 'then' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    if (!(tokenList[*pos].type == TokenType::IF && tokenList[*pos].value == "else")) {
        std::cout << "Expected 'else' keyword after '}' of 'then' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    if (tokenList[*pos].type != TokenType::LEFT_CURLY_BRACKET) {
        std::cout << "Expected '{' keyword after 'else' keyword of 'if' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    auto elseBody = factory.createParser(STATEMENT_LIST, tokenList, pos)->parse();
    if (tokenList[*pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        std::cout << "Expected '}' keyword after stmtList of 'else' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    ifNode.children.push_back(condChild);
    ifNode.children.push_back(thenBody);
    ifNode.children.push_back(elseBody);
    return ifNode;
}

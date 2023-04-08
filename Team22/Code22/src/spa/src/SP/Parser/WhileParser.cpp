
#include "WhileParser.h"

TNode WhileParser::parse() {
    Token currToken = tokenList[*pos];
    TNode whileNode;
    whileNode.nodeType = currToken.type;
    whileNode.stringId = currToken.value;
    whileNode.stmtNumber = currToken.lineNumber;
    if (currToken.type != TokenType::WHILE) {
        std::cout << "Expected 'while' keyword for the statement but instead got: " << currToken.value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token next = tokenList[++*pos];
    if (next.type != TokenType::LEFT_ROUND_BRACKET) {
        std::cout << "Expected '(' after while keyword but instead got: " << next.value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    ParserFactory factory;
    auto condChild = factory.createParser(CONDITIONAL_EXPR, tokenList, pos)->parse();
    if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        std::cout << "Expected ')' after conditional expr in 'while' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }

    ++*pos;
    if (tokenList[*pos].type != TokenType::LEFT_CURLY_BRACKET) {
        std::cout << "Expected '{' after conditional expr in 'while' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    auto whileBody = factory.createParser(STATEMENT_LIST, tokenList, pos)->parse();
    if (tokenList[*pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        std::cout << "Expected '}' after stmtList in 'while' but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    whileNode.children.push_back(condChild);
    whileNode.children.push_back(whileBody);
    return whileNode;
}

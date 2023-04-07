//
// Created by Yi Zhang on 3/4/23.
//

#include "AssignParser.h"

TNode AssignParser::parse() {
    Token currToken = tokenList[*pos];
    TNode assignNode;
    assignNode.nodeType = TokenType::ASSIGN;
    assignNode.stringId = "assign";
    assignNode.stmtNumber = currToken.lineNumber;
    //lhs, var Node
    TNode lhs;
    lhs.nodeType = currToken.type;
    lhs.stringId = currToken.value;
    lhs.stmtNumber = currToken.lineNumber;
    assignNode.children.push_back(lhs);
    Token assignOperator = tokenList[++*pos];
    if (assignOperator.type != TokenType::OPERATOR || assignOperator.value != "=") {
        std::cout << "Expected '=' sign for the assignment statement but instead got: " << assignOperator.value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    //rhs, expr Node
    ++*pos;
    ParserFactory factory;
    auto rhs = factory.createParser(EXPR, tokenList, pos)->parse();
    assignNode.children.push_back(rhs);
    Token following = tokenList[*pos];
    if (following.type != TokenType::STATEMENT_TERMINAL) {
        std::cout << "Expected statement terminal ';' but instead got: " << following.value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    return assignNode;
}

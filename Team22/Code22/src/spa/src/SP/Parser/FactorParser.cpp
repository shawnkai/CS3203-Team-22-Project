//
// Created by Yi Zhang on 6/4/23.
//

#include "FactorParser.h"

/**
 * Parse the 'factor' of SIMPLE Source.
 *
 * @return an AST representation of a factor
 */
TNode FactorParser::parse() {
    TNode node;
    Token currToken = tokenList[*pos];
    if (currToken.type == TokenType::LEFT_ROUND_BRACKET) {
        ++*pos;
        ParserFactory expressionParserFactory;
        auto exprParser = expressionParserFactory.createParser(EXPR, tokenList, pos);
        TNode node1 = exprParser->parse();
        currToken = tokenList[*pos];
        if (currToken.type != TokenType::RIGHT_ROUND_BRACKET) {
            std::cout << "in factor parser Expected closing bracket ')' but instead got: " << currToken.value << std::endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++*pos;
        return node1;
    }
    if (currToken.type == TokenType::NAME_IDENTIFIER) {
        node.stringId = currToken.value;
        node.stmtNumber = currToken.lineNumber;
        node.nodeType = currToken.type;
        ++*pos;
    } else {
        if (currToken.type != TokenType::INTEGER) {
            std::cout << "Expected constant or variable but instead got: " << currToken.value << std::endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        node.nodeType = currToken.type;
        node.stringId = currToken.value;
        node.stmtNumber = currToken.lineNumber;
        ++*pos;
    }
    return node;
}

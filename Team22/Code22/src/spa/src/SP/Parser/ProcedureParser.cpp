//
// Created by Yi Zhang on 3/4/23.
//

#include "ProcedureParser.h"

/**
 * Parse one single procedure of a SIMPLE Source.
 *
 * @return an AST representation of a procedure
 */
TNode ProcedureParser::parse() {
    Token currToken = tokenList[*pos];
    TNode node;
    node.nodeType = TokenType::PROCEDURE;
    ++*pos;
    if (tokenList[*pos].type != TokenType::NAME_IDENTIFIER) {
        std::cout << "Expecting function name for a procedure, got something else" << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    node.stringId = tokenList[*pos].value;
    node.stmtNumber = tokenList[*pos].lineNumber;
    ++*pos;
    if (*pos >= tokenList.size()) {
        std::cout << "SIMPLE source end unexpectedly after a procedure name" << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token nextToken = tokenList[*pos];
    if (nextToken.type != TokenType::LEFT_CURLY_BRACKET) {
        std::cout << "Expecting '{' after procedure name declaration but got:" << nextToken.value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    if (*pos >= tokenList.size()) {
        std::cout << "SIMPLE source end unexpectedly after left curly bracket" << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token stmtToken = tokenList[*pos];
    // Recursion happens in the stmtList node
    ParserFactory stmtListParserFactory;
    auto stmtParser = stmtListParserFactory.createParser(STATEMENT_LIST, tokenList, pos);
    auto child = stmtParser->parse();
    node.children.push_back(child);
    if (*pos >= tokenList.size()) {
        std::cout << "SIMPLE source end unexpectedly without right curly bracket" << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    if (tokenList[*pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        std::cout << "Expected '}' at the end of a procedure but instead got: " << tokenList[*pos].value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++*pos;
    return node;
}

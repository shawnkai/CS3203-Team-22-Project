//
// Created by Yi Zhang on 3/4/23.
//

#include "ReadParser.h"

/**
 * Parse one single read statement, which has exactly one child.
 *
 * @return an AST representation of the print statement
 */
TNode ReadParser::parse() {
    Token currToken = tokenList[*pos];
    TNode node;
    node.nodeType = currToken.type;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::READ) {
        std::cout << "Expected read keyword for the statement but instead got: " << currToken.value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    int checkerPos = *pos + 2;
    if (checkerPos >= tokenList.size()) {
        std::cout << "SIMPLE source end unexpectedly after read keyword, with no stmt terminal" << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        std::cout << "Expected stmt terminal ';' after variable name, but got " << pendingCheckTerminalToken.value << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token varNameToken = tokenList[++*pos];
    TNode childNode;
    childNode.nodeType = varNameToken.type;
    childNode.stringId = varNameToken.value;
    childNode.stmtNumber = varNameToken.lineNumber;
    // increment pos by 2 because we have verified the existence of statement terminal ';'
    *pos += 2;
    node.children.push_back(childNode);
    return node;
}

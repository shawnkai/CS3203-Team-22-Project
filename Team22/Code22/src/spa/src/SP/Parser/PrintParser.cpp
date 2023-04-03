//
// Created by Yi Zhang on 3/4/23.
//

#include "PrintParser.h"

TreeNode PrintParser::parse() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = currToken.type;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::PRINT) {
        cout << "Expected print keyword for the statement but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    int checkerPos = pos + 2;
    if (checkerPos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after print keyword, with no ';' " << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected stmt terminal ';' after variable name, but got " << pendingCheckTerminalToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }

    Token varNameToken = tokenList[++pos];
    TNode child;
    child.nodeType = varNameToken.type;
    child.stringId = varNameToken.value;
    child.stmtNumber = varNameToken.lineNumber;
    node.children.push_back(child);
    pos += 2;
    return node;
}
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <utility>

using namespace std;
#include "Parser.h"
#include "TNode.h"

TNode Parser::Parse() {
    Token currToken = tokenList[pos];
    ++pos;
    if (currToken.type != TokenType::PROCEDURE) {
        cerr << "Expecting keyword procedure for a legal SIMPLE program" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    return parseProcedure();
}

TNode Parser::parseProcedure() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = TokenType::PROCEDURE;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;
    if (currToken.type != TokenType::NAME_IDENTIFIER) {
        cerr << "Expecting function name for a procedure, got something else" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++pos;
    if (pos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after a procedure name" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token nextToken = tokenList[pos];
    if (nextToken.type != TokenType::LEFT_CURLY_BRACKET) {
        cerr << "Expecting '{' after procedure name declaration but got:" << nextToken.value <<endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++pos;
    if (pos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token stmtToken = tokenList[pos];
    while (stmtToken.type != TokenType::RIGHT_CURLY_BRACKET) {
        auto childNode = parseStatement();
        if (childNode.children.size() < 1) {
            cerr << "empty SIMPLE Programme with no statement received" << endl;
            return static_cast<TNode>(static_cast<TokenType>(NULL));
        }
        node.children.push_back(childNode);
        stmtToken = tokenList[pos];
    }
    ++pos;
    return node;
}

TNode Parser::parseStatement() {
    if (pos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token currToken = tokenList[pos];
    TNode stmtNode;
    stmtNode.nodeType = TokenType::STATEMENT_LIST;
    stmtNode.stringId = "stmtList";
    stmtNode.stmtNumber = currToken.lineNumber;
    if (currToken.type == TokenType::READ) {
        auto childNode = parseReadStatement();
        stmtNode.children.push_back(childNode);
        return stmtNode;
    }
    return static_cast<TNode>(static_cast<TokenType>(NULL));
}

TNode Parser::parseReadStatement() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = currToken.type;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::READ) {
        cerr << "Expected read keyword for the statement but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    int checkerPos = pos + 2;
    if (checkerPos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after read keyword, with no stmt terminal" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        cerr << "Expected stmt terminal ';' after variable name, but got " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token varNameToken = tokenList[++pos];
    TNode childNode;
    childNode.nodeType = varNameToken.type;
    childNode.stringId = varNameToken.value;
    childNode.stmtNumber = varNameToken.lineNumber;
    // increment pos by 2 because we have verified the existence of statement terminal ';'
    pos += 2;
    node.children.push_back(childNode);
    return node;
}

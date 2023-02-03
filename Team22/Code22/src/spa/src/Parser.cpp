#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#include "Parser.h"
#include "TNode.h"

unique_ptr<TNode> Parser::Parse() {
    auto node = make_unique<TNode>();
    node->nodeType = TokenType::PROCEDURE;
    node->stringId = ToString(TokenType::PROCEDURE);
    node->stmtNumber = tokenList[pos].lineNumber;
    Token currToken = tokenList[pos];
    ++pos;
    if (currToken.type != TokenType::PROCEDURE) {
        cerr << "Expecting keyword procedure for a legal SIMPLE program" << endl;
        return nullptr;
    }
    node->children.push_back(parseProcedure());
    return node;
}

unique_ptr<TNode> Parser::parseProcedure() {
    Token currToken = tokenList[pos];
    auto node = make_unique<TNode>();
    node->nodeType = currToken.type;
    node->stringId = currToken.value;
    node->stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::NAME_IDENTIFIER) {
        cerr << "Expecting function name for a procedure, got something else" << endl;
        return nullptr;
    }
    ++pos;
    if (pos >= size(tokenList)) {
        cerr << "SIMPLE source end unexpectedly after a procedure name" << endl;
        return nullptr;
    }
    Token nextToken = tokenList[pos];
    if (nextToken.type != TokenType::LEFT_CURLY_BRACKET) {
        cerr << "Expecting '{' after procedure name declaration but got:" << nextToken.value <<endl;
        return nullptr;
    }
    ++pos;
    if (pos >= size(tokenList)) {
        cerr << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return nullptr;
    }
    Token stmtToken = tokenList[pos];
    while (stmtToken.type != TokenType::RIGHT_CURLY_BRACKET) {
        auto childNode = parseStatement();
        if (!childNode) {
            return nullptr;
        }
        node->children.push_back(std::move(childNode));
    }
    ++pos;
    return node;
}

unique_ptr<TNode> Parser::parseStatement() {
    if (pos >= size(tokenList)) {
        cerr << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return nullptr;
    }
    Token currToken = tokenList[pos];
    auto node = make_unique<TNode>();
    node->nodeType = TokenType::STATEMENT_LIST;
    node->stringId = "";
    node->stmtNumber = currToken.lineNumber;
    if (currToken.type == TokenType::READ) {
        auto childNode = parseReadStatement();
        node->children.push_back(std::move(childNode));
        return node;
    }
    return nullptr;
}

unique_ptr<TNode> Parser::parseReadStatement() {
    Token currToken = tokenList[pos];
    auto node = std::make_unique<TNode>();
    node->nodeType = currToken.type;
    node->stringId = currToken.value;
    node->stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::READ) {
        cerr << "Expected read keyword for the statement but instead got: " << currToken.value << endl;
        return nullptr;
    }
    int checkerPos = pos + 2;
    if (checkerPos >= size(tokenList)) {
        cerr << "SIMPLE source end unexpectedly after read keyword, with no stmt terminal" << endl;
        return nullptr;
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        cerr << "Expected stmt terminal ';' after variable name, but got " << currToken.value << endl;
        return nullptr;
    }
    Token varNameToken = tokenList[++pos];
    auto varChildNode = std::make_unique<TNode>();
    varChildNode->nodeType = varNameToken.type;
    varChildNode->stringId = varNameToken.value;
    varChildNode->stmtNumber = varNameToken.lineNumber;

    node->children.push_back(std::move(varChildNode));

    return node;
}

int dummy() {
    return 0;
}

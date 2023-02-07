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
        //*node = stmtNode;
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

//int main() {
//    vector<Token> testList;
//    Token t1 = Token(TokenType::PROCEDURE, "procedure", 0);
//    Token t2 = Token(TokenType::NAME_IDENTIFIER, "main", 0);
//    Token t3 = Token(TokenType::LEFT_CURLY_BRACKET, "{", 0);
//    Token t4 = Token(TokenType::READ, "read", 1);
//    Token t5 = Token(TokenType::NAME_IDENTIFIER, "x", 1);
//    Token t6 = Token(TokenType::STATEMENT_TERMINAL, ";", 1);
//    Token t7 = Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2);
//    testList.push_back(t1);
//    testList.push_back(t2);
//    testList.push_back(t3);
//    testList.push_back(t4);
//    testList.push_back(t5);
//    testList.push_back(t6);
//    testList.push_back(t7);
//    Parser testParser = Parser(testList);
//
//    TNode result = testParser.Parse();
//    if (result.children.empty()) {
//        cout << "Null pointer returned, use debug mode to find out why" << endl;
//    }
//    std::queue<TNode> pendingToString;
//    pendingToString.push(result);
//    while (!pendingToString.empty()) {
//        auto toProcess = pendingToString.front();
//        pendingToString.pop();
//        cout << ToString(toProcess) << endl;
//        if (!toProcess.children.empty()) {
//            auto childrenArr = (toProcess).children;
//            for (TNode child: childrenArr) {
//                pendingToString.push(child);
//            }
//        }
//    }
//    return 0;
//};

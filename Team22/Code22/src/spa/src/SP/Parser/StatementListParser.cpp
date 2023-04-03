//
// Created by Yi Zhang on 3/4/23.
//

#include "StatementListParser.h"

std::shared_ptr<TreeNode> StatementListParser::parse() {
    if (*pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token currToken = tokenList[*pos];
    StatementListNode stmtNode;
    stmtNode.nodeType = TokenType::STATEMENT_LIST;
    int checkerPos = *pos - 2;
    if (tokenList[checkerPos].type == TokenType::IF &&
        (tokenList[checkerPos].value == "then" || tokenList[checkerPos].value == "else")) {
        stmtNode.stringId = tokenList[checkerPos].value;
        stmtNode.stmtNumber = tokenList[checkerPos].lineNumber;
    } else {
        stmtNode.stringId = "stmtList";
        stmtNode.stmtNumber = currToken.lineNumber;
    }
    while (tokenList[*pos].type != TokenType::RIGHT_CURLY_BRACKET && pos < tokenList.size()) {
        if (*pos >= tokenList.size()) {
            cout << "SIMPLE source procedure ends unexpectedly without right curly bracket" << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        if (tokenList[*pos].type == TokenType::READ) {
            ReadParserFactory readParserFactory;
            auto readParser = readParserFactory.createParser(tokenList, pos);
            auto childNode = readParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::PRINT) {
            PrintParserFactory printParserFactory;
            auto printParser = printParserFactory.createParser(tokenList, pos);
            auto childNode = printParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::WHILE) {
            WhileParserFactory whileParserFactory;
            auto whileParser = whileParserFactory.createParser(tokenList, pos);
            auto childNode = whileParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::IF) {
            auto childNode = parseIfStatement();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::NAME_IDENTIFIER) {
            auto childNode = parseAssignStatement();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::CALL) {
            auto childNode = parseCallStatement();
            stmtNode.children.push_back(childNode);
        }
        else {
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Unrecognized Token");
        }
    }
    return stmtNode;
}
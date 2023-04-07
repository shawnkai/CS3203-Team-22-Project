//
// Created by Yi Zhang on 3/4/23.
//

#include "StatementListParser.h"

TNode StatementListParser::parse() {
    if (*pos >= tokenList.size()) {
        std::cout << "SIMPLE source end unexpectedly after left curly bracket" << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token currToken = tokenList[*pos];
    TNode stmtNode;
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
    while (tokenList[*pos].type != TokenType::RIGHT_CURLY_BRACKET && *pos < tokenList.size()) {
        if (*pos >= tokenList.size()) {
            std::cout << "SIMPLE source procedure ends unexpectedly without right curly bracket" << std::endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        if (tokenList[*pos].type == TokenType::READ) {
            ParserFactory readParserFactory;
            auto readParser = readParserFactory.createParser(READ, tokenList, pos);
            auto childNode = readParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::PRINT) {
            ParserFactory printParserFactory;
            auto printParser = printParserFactory.createParser(PRINT, tokenList, pos);
            auto childNode = printParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::WHILE) {
            ParserFactory whileParserFactory;
            auto whileParser = whileParserFactory.createParser(WHILE, tokenList, pos);
            auto childNode = whileParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::IF) {
            ParserFactory ifParserFactory;
            auto ifParser = ifParserFactory.createParser(IF, tokenList, pos);
            auto childNode = ifParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::NAME_IDENTIFIER) {
            ParserFactory assignParserFactory;
            auto assignParser = assignParserFactory.createParser(ASSIGN, tokenList, pos);
            auto childNode = assignParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[*pos].type == TokenType::CALL) {
            ParserFactory callParserFactory;
            auto callParser = callParserFactory.createParser(CALL, tokenList, pos);
            auto childNode = callParser->parse();
            stmtNode.children.push_back(childNode);
        }
        else {
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Unrecognized Token");
        }
    }
    return stmtNode;
}

//
// Created by Yi Zhang on 3/4/23.
//

#include "ProcedureParser.h"

TreeNode ProcedureParser::parse() {
    Token currToken = tokenList[*pos];
    ProcedureNode node;
    node.nodeType = TokenType::PROCEDURE;
    ++ *pos;
    if (tokenList[*pos].type != TokenType::NAME_IDENTIFIER) {
        cout << "Expecting function name for a procedure, got something else" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    node.stringId = tokenList[*pos].value;
    node.stmtNumber = tokenList[*pos].lineNumber;
    ++ *pos;
    if (*pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after a procedure name" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token nextToken = tokenList[*pos];
    if (nextToken.type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expecting '{' after procedure name declaration but got:" << nextToken.value <<endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ *pos;
    if (*pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token stmtToken = tokenList[*pos];
    // Recursion happens in the stmtList node
    StatementListParserFactory stmtListParserFactory;
    auto stmtParser = stmtListParserFactory.createParser(tokenList, pos);
    auto child = stmtParser->parse();
    node.children.push_back(child);
    if (*pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly without right curly bracket" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    if (tokenList[*pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' at the end of a procedure but instead got: " << tokenList[*pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ *pos;
    return node;
}

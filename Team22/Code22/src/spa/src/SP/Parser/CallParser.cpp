//
// Created by Yi Zhang on 3/4/23.
//

#include "CallParser.h"

std::shared_ptr<TreeNode> CallParser::parse() {
    Token currToken = tokenList[*pos];
    ++ *pos;
    CallNode callNode;
    callNode.nodeType = TokenType::CALL;
    callNode.stmtNumber = currToken.lineNumber;
    if (tokenList[*pos].type != TokenType::NAME_IDENTIFIER) {
        cout << "Expected procedure name for a CALL stmt but instead got: " << tokenList[*pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    callNode.stringId = tokenList[*pos].value;
    ++ *pos;
    if (tokenList[*pos].type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected statement terminal ';' but instead got: " << tokenList[*pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ *pos;
    return std::make_shared<CallNode>(callNode);
}

//
// Created by Yi Zhang on 4/4/23.
//

#include "ExpressionParser.h"

std::shared_ptr<TreeNode> ExpressionParser::parse() {
    auto node = parseTerm();
    while (tokenList[*pos].type == TokenType::OPERATOR && (tokenList[*pos].value == "+" || tokenList[*pos].value == "-")) {
        Token currToken = tokenList[*pos];
        TreeNode opNode;
        opNode.nodeType = currToken.type;
        opNode.stringId = currToken.value;
        opNode.stmtNumber = currToken.lineNumber;
        opNode.children.push_back(node);
        ++ *pos;
        opNode.children.push_back(parseTerm());
        node = opNode;
    }
    return node;
}
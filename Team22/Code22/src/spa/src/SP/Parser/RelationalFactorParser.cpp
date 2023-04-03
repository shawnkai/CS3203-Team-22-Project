//
// Created by Yi Zhang on 4/4/23.
//

#include "RelationalFactorParser.h"

std::shared_ptr<TreeNode> RelationalFactorParser::parse() {
    TreeNode node;
    Token currToken = tokenList[*pos];
    if (currToken.type == TokenType::NAME_IDENTIFIER || currToken.type == TokenType::INTEGER) {
        int peekPos = *pos + 1;
        if (tokenList[peekPos].type == TokenType::RIGHT_ROUND_BRACKET ||
            (tokenList[peekPos].type == TokenType::OPERATOR &&
            (tokenList[peekPos].value == ">" || tokenList[peekPos].value == ">="
            || tokenList[peekPos].value == "<=" ||tokenList[peekPos].value == "<"
            || tokenList[peekPos].value == "==" || tokenList[peekPos].value == "!="))) {
            TreeNode varNode;
            varNode.nodeType = currToken.type;
            varNode.stringId = currToken.value;
            varNode.stmtNumber = currToken.lineNumber;
            node = varNode;
            ++ *pos;
        }
        else {
            node = parseExpression();
        }
    } else {
        node = parseExpression();
    }
    return std::make_shared<TreeNode>(node);
}
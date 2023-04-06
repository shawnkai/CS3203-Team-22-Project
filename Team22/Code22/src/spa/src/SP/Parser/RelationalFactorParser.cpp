//
// Created by Yi Zhang on 4/4/23.
//

#include "RelationalFactorParser.h"

std::shared_ptr<TreeNode> RelationalFactorParser::parse() {
    RelationalFactorNode node;
    Token currToken = tokenList[*pos];
    ParserFactory factory;
    if (currToken.type == TokenType::NAME_IDENTIFIER || currToken.type == TokenType::INTEGER) {
        int peekPos = *pos + 1;
        if (tokenList[peekPos].type == TokenType::RIGHT_ROUND_BRACKET ||
            (tokenList[peekPos].type == TokenType::OPERATOR &&
            (tokenList[peekPos].value == ">" || tokenList[peekPos].value == ">="
            || tokenList[peekPos].value == "<=" ||tokenList[peekPos].value == "<"
            || tokenList[peekPos].value == "==" || tokenList[peekPos].value == "!="))) {
            RelationalFactorNode varNode;
            varNode.nodeType = currToken.type;
            varNode.stringId = currToken.value;
            varNode.stmtNumber = currToken.lineNumber;
            node = varNode;
            ++ *pos;
            return std::make_shared<TreeNode>(node);
        } else {
            return factory.createParser(EXPR, tokenList, pos)->parse();
        }
    } else {
        return factory.createParser(EXPR, tokenList, pos)->parse();
    }
}

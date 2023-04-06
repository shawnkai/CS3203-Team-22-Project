//
// Created by Yi Zhang on 4/4/23.
//

#include "ExpressionParser.h"

std::shared_ptr<TreeNode> ExpressionParser::parse() {
    ParserFactory termParserFactory;
    auto termParser = termParserFactory.createParser(TERM, tokenList, pos);
    auto node = *termParser->parse();
    while (tokenList[*pos].type == TokenType::OPERATOR && (tokenList[*pos].value == "+" || tokenList[*pos].value == "-")) {
        Token currToken = tokenList[*pos];
        ExpressionNode opNode;
        opNode.nodeType = currToken.type;
        opNode.stringId = currToken.value;
        opNode.stmtNumber = currToken.lineNumber;
        opNode.children.push_back(std::make_shared<TreeNode>(node));
        ++ *pos;
        opNode.children.push_back(termParser->parse());
        node = opNode;
    }
    return std::make_shared<TreeNode>(node);
}

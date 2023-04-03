
#include "RelationalExprParser.h"

std::shared_ptr<TreeNode> RelationalExprParser::parse() {
    TreeNode node = parseRelationalFactor();
    TNode relationalNode;
    while (tokenList[pos].type == TokenType::OPERATOR &&
           (tokenList[pos].value == ">" || tokenList[pos].value == "<" || tokenList[pos].value == ">="
            || tokenList[pos].value == "<=" || tokenList[pos].value == "==" || tokenList[pos].value == "!=")) {
        relationalNode.nodeType = TokenType::OPERATOR;
        relationalNode.stringId = tokenList[pos].value;
        relationalNode.stmtNumber = tokenList[pos].lineNumber;
        relationalNode.children.push_back(node);
        ++ pos;
        relationalNode.children.push_back(parseRelationalFactor());
    }
    return relationalNode;
}
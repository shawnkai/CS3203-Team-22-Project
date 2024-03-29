
#include "RelationalExprParser.h"

/**
 * Parse the 'rel_expr' of SIMPLE Source.
 *
 * @return an AST representation of a relational expression
 */
TNode RelationalExprParser::parse() {
    ParserFactory factory;
    auto node = factory.createParser(RELATIONAL_FACTOR, tokenList, pos)->parse();
    TNode relationalNode;
    while (tokenList[*pos].type == TokenType::OPERATOR &&
           (tokenList[*pos].value == ">" || tokenList[*pos].value == "<" || tokenList[*pos].value == ">=" || tokenList[*pos].value == "<=" || tokenList[*pos].value == "==" || tokenList[*pos].value == "!=")) {
        relationalNode.nodeType = TokenType::OPERATOR;
        relationalNode.stringId = tokenList[*pos].value;
        relationalNode.stmtNumber = tokenList[*pos].lineNumber;
        relationalNode.children.push_back(node);
        ++*pos;
        relationalNode.children.push_back(factory.createParser(RELATIONAL_FACTOR, tokenList, pos)->parse());
    }
    return relationalNode;
}

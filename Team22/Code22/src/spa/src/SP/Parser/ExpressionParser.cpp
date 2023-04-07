//
// Created by Yi Zhang on 4/4/23.
//

#include "ExpressionParser.h"

TNode ExpressionParser::parse() {
    ParserFactory termParserFactory;
    auto termParser = termParserFactory.createParser(TERM, tokenList, pos);
    auto node = termParser->parse();
    while (tokenList[*pos].type == TokenType::OPERATOR && (tokenList[*pos].value == "+" || tokenList[*pos].value == "-")) {
        Token currToken = tokenList[*pos];
        TNode opNode;
        opNode.nodeType = currToken.type;
        opNode.stringId = currToken.value;
        opNode.stmtNumber = currToken.lineNumber;
        opNode.children.push_back(node);
        ++ *pos;
        opNode.children.push_back(termParser->parse());
        node = opNode;
    }
    return node;
}

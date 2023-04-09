//
// Created by Yi Zhang on 6/4/23.
//

#include "TermParser.h"

/**
 * Parse the 'term' of SIMPLE Source.
 *
 * @return an AST representation of a term
 */
TNode TermParser::parse() {
    ParserFactory factorParserFactory;
    auto factorParser = factorParserFactory.createParser(FACTOR, tokenList, pos);
    auto node = factorParser->parse();
    while (tokenList[*pos].type == TokenType::OPERATOR &&
           (tokenList[*pos].value == "*" || tokenList[*pos].value == "/" || tokenList[*pos].value == "%")) {
        Token currToken = tokenList[*pos];
        TNode termNode;
        termNode.nodeType = TokenType::OPERATOR;
        termNode.stringId = currToken.value;
        termNode.stmtNumber = currToken.lineNumber;
        termNode.children.push_back(node);
        ++*pos;
        termNode.children.push_back(factorParser->parse());
        node = termNode;
    }
    return node;
}

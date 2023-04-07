
#include "ProgramParser.h"

TNode ProgramParser::parse() {
    Token currToken = tokenList[*pos];
    if (currToken.type != TokenType::PROCEDURE) {
        std::cout << "Expecting keyword procedure for a legal SIMPLE program" << std::endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    TNode programNode;
    programNode.nodeType = TokenType::PROGRAM;
    programNode.stringId = currToken.value;
    programNode.stmtNumber = currToken.lineNumber;
    while (*pos < tokenList.size() && tokenList[*pos].type == TokenType::PROCEDURE) {
        ParserFactory procedureParserFactory;
        auto procedureParser = procedureParserFactory.createParser(PROCEDURE, tokenList, pos);
        TNode procedureNode = procedureParser->parse();
        programNode.children.push_back(procedureNode);
    }
    if (*pos != tokenList.size()) {
        std::cout << "Tangling tokens outside the last procedure are ignored" << std::endl;
    }
    return programNode;
}

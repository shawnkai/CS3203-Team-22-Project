
#include "ProgramParser.h"

std::shared_ptr<TreeNode> ProgramParser::parse() {
    Token currToken = tokenList[*pos];
    if (currToken.type != TokenType::PROCEDURE) {
        cout << "Expecting keyword procedure for a legal SIMPLE program" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ProgramNode programNode;
    programNode.nodeType = TokenType::PROGRAM;
    programNode.stringId = currToken.value;
    programNode.stmtNumber = currToken.lineNumber;
    while (*pos < tokenList.size() && tokenList[*pos].type == TokenType::PROCEDURE) {
        ProcedureParserFactory procedureParserFactory;
        auto procedureParser = procedureParserFactory.createParser(tokenList, pos);
        std::shared_ptr<TreeNode> procedureNode = procedureParser->parse();
        programNode.children.push_back(procedureNode);
    }
    if (*pos != tokenList.size()) {
        cout << "Tangling tokens outside the last procedure are ignored" << endl;
    }
    return make_shared<TreeNode>(programNode);
}

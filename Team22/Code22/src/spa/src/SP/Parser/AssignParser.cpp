//
// Created by Yi Zhang on 3/4/23.
//

#include "AssignParser.h"

std::shared_ptr<TreeNode> AssignParser::parse() {
    Token currToken = tokenList[*pos];
    AssignNode assignNode;
    assignNode.nodeType = TokenType::ASSIGN;
    assignNode.stringId = "assign";
    assignNode.stmtNumber = currToken.lineNumber;
    //lhs, var Node
    VarNode lhs;
    lhs.nodeType = currToken.type;
    lhs.stringId = currToken.value;
    lhs.stmtNumber = currToken.lineNumber;
    assignNode.children.push_back(std::make_shared<TreeNode>(lhs));
    Token assignOperator = tokenList[++ *pos];
    if (assignOperator.type != TokenType::OPERATOR || assignOperator.value != "=") {
        cout << "Expected '=' sign for the assignment statement but instead got: " << assignOperator.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    //rhs, expr Node
    ++ *pos;
    ParserFactory factory;
    auto rhs = factory.createParser(EXPR, tokenList, pos)->parse();
    assignNode.children.push_back(rhs);
    Token following = tokenList[*pos];
    if (following.type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected statement terminal ';' but instead got: " << following.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ *pos;
    return std::make_shared<AssignNode>(assignNode);
}

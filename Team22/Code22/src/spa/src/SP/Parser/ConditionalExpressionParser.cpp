//
// Created by Yi Zhang on 4/4/23.
//

#include "ConditionalExpressionParser.h"

std::shared_ptr<TreeNode> ConditionalExpressionParser::parse() {
    Token currToken = tokenList[*pos];
    TreeNode condNode;
    if (tokenList[*pos].type == TokenType::OPERATOR && currToken.value == "!") {
        condNode.nodeType = currToken.type;
        condNode.stringId = "neg";
        condNode.stmtNumber = currToken.lineNumber;
        ++ *pos;
        if (tokenList[*pos].type != TokenType::LEFT_ROUND_BRACKET) {
            cout << "Expected '(' after negation sign '!' but instead got: " << tokenList[pos].value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ *pos;
        ConditionalExpressionParserFactory conditionalExpressionParserFactory;
        auto condParser = conditionalExpressionParserFactory.createParser(tokenList, pos);
        condNode.children.push_back(condParser->parse());
        if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cout << "Expected ')' after a conditional expr but instead got: " << tokenList[*pos].value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ *pos;
        return std::make_shared<TreeNode>(condNode);
    } else if (tokenList[*pos].type == TokenType::LEFT_ROUND_BRACKET) {
        // find matching right round bracket and check if it is && or || operator
        int recorder = -1;
        int stack = 0;
        bool flag = false;
        for (int i = *pos; i < tokenList.size(); i++ ) {
            Token underExamine = tokenList[i];
            if (underExamine.type == TokenType::LEFT_ROUND_BRACKET) {
                ++ stack;
                flag = true;
            } else if (underExamine.type == TokenType::RIGHT_ROUND_BRACKET) {
                -- stack;
            }
            if (stack == 0 && flag) {
                recorder = i + 1;
                break;
            }
        }
        // otherwise, return relational expression node
        if(!(tokenList[recorder].value == "&&" || tokenList[recorder].value == "||")) {
            return parseRelationalExpr();
        }
        ++ *pos;
        condNode = parseConditionalExpr();
        if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cout << "Expected ')' after a conditional expr but instead got: " << tokenList[*pos].value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ *pos;
        if (tokenList[*pos].type == TokenType::OPERATOR && tokenList[*pos].value == "&&") {
            TNode andNode;
            andNode.nodeType = TokenType::OPERATOR;
            andNode.stringId = "and";
            andNode.stmtNumber = tokenList[*pos].lineNumber;
            ++ *pos;
            if (tokenList[*pos].type != TokenType::LEFT_ROUND_BRACKET) {
                cout << "Expected '(' after '&&' operator but instead got: " << tokenList[*pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            andNode.children.push_back(condNode);
            ++ *pos;
            andNode.children.push_back(parseConditionalExpr());
            if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++ *pos;
            return andNode;
        } else {
            if (tokenList[*pos].value != "||") {
                cout << "Expected '&&' or '||' operator but instead got: " << tokenList[*pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            TNode orNode;
            orNode.nodeType = TokenType::OPERATOR;
            orNode.stringId = "or";
            orNode.stmtNumber = tokenList[*pos].lineNumber;
            ++ *pos;
            if (tokenList[*pos].type != TokenType::LEFT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            orNode.children.push_back(condNode);
            ++ *pos;
            orNode.children.push_back(parseConditionalExpr());
            if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++ *pos;
            return orNode;
        }
    } else {
        return parseRelationalExpr();
    }
}
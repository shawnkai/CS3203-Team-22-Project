//
// Created by Yi Zhang on 4/4/23.
//

#include "ConditionalExpressionParser.h"

/**
 * Parse the 'cond_expr' of SIMPLE Source.
 *
 * @return an AST representation of a conditional expression
 */
TNode ConditionalExpressionParser::parse() {
    Token currToken = tokenList[*pos];
    TNode condNode;
    if (tokenList[*pos].type == TokenType::OPERATOR && currToken.value == "!") {
        condNode.nodeType = currToken.type;
        condNode.stringId = "neg";
        condNode.stmtNumber = currToken.lineNumber;
        ++*pos;
        if (tokenList[*pos].type != TokenType::LEFT_ROUND_BRACKET) {
            std::cout << "Expected '(' after negation sign '!' but instead got: " << tokenList[*pos].value << std::endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++*pos;
        condNode.children.push_back(parse());
        if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            std::cout << "Expected ')' after a conditional expr but instead got: " << tokenList[*pos].value << std::endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++*pos;
        return condNode;
    } else if (tokenList[*pos].type == TokenType::LEFT_ROUND_BRACKET) {
        // find matching right round bracket and check if it is && or || operator
        int recorder = -1;
        int stack = 0;
        bool flag = false;
        for (int i = *pos; i < tokenList.size(); i++) {
            Token underExamine = tokenList[i];
            if (underExamine.type == TokenType::LEFT_ROUND_BRACKET) {
                ++stack;
                flag = true;
            } else if (underExamine.type == TokenType::RIGHT_ROUND_BRACKET) {
                --stack;
            }
            if (stack == 0 && flag) {
                recorder = i + 1;
                break;
            }
        }
        // otherwise, return relational expression node
        ParserFactory factory;
        if (!(tokenList[recorder].value == "&&" || tokenList[recorder].value == "||")) {
            return factory.createParser(RELATIONAL_EXPR, tokenList, pos)->parse();
        }
        ++*pos;
        auto condNodeLeft = parse();
        if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            std::cout << "Expected ')' after a conditional expr but instead got: " << tokenList[*pos].value << std::endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++*pos;
        if (tokenList[*pos].type == TokenType::OPERATOR && tokenList[*pos].value == "&&") {
            TNode andNode;
            andNode.nodeType = TokenType::OPERATOR;
            andNode.stringId = "and";
            andNode.stmtNumber = tokenList[*pos].lineNumber;
            ++*pos;
            if (tokenList[*pos].type != TokenType::LEFT_ROUND_BRACKET) {
                std::cout << "Expected '(' after '&&' operator but instead got: " << tokenList[*pos].value << std::endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            andNode.children.push_back(condNodeLeft);
            ++*pos;
            andNode.children.push_back(parse());
            if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                std::cout << "Expected ')' after a conditional expr but instead got: " << tokenList[*pos].value << std::endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++*pos;
            return andNode;
        } else {
            if (tokenList[*pos].value != "||") {
                std::cout << "Expected '&&' or '||' operator but instead got: " << tokenList[*pos].value << std::endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            TNode orNode;
            orNode.nodeType = TokenType::OPERATOR;
            orNode.stringId = "or";
            orNode.stmtNumber = tokenList[*pos].lineNumber;
            ++*pos;
            if (tokenList[*pos].type != TokenType::LEFT_ROUND_BRACKET) {
                std::cout << "Expected ')' after a conditional expr but instead got: " << tokenList[*pos].value << std::endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            orNode.children.push_back(condNodeLeft);
            ++*pos;
            orNode.children.push_back(parse());
            if (tokenList[*pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                std::cout << "Expected ')' after a conditional expr but instead got: " << tokenList[*pos].value << std::endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++*pos;
            return orNode;
        }
    } else {
        ParserFactory factory;
        return factory.createParser(RELATIONAL_EXPR, tokenList, pos)->parse();
    }
}

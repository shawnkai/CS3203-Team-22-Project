#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <utility>

using namespace std;
#include "Parser.h"
#include "TNode.h"

TNode Parser::Parse() {
    Token currToken = tokenList[pos];
    ++pos;
    if (currToken.type != TokenType::PROCEDURE) {
        cerr << "Expecting keyword procedure for a legal SIMPLE program" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    return parseProcedure();
}

TNode Parser::parseProcedure() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = TokenType::PROCEDURE;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;
    if (currToken.type != TokenType::NAME_IDENTIFIER) {
        cerr << "Expecting function name for a procedure, got something else" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++pos;
    if (pos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after a procedure name" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token nextToken = tokenList[pos];
    if (nextToken.type != TokenType::LEFT_CURLY_BRACKET) {
        cerr << "Expecting '{' after procedure name declaration but got:" << nextToken.value <<endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++pos;
    if (pos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token stmtToken = tokenList[pos];
    // Recursion should happen in the stmtList node
    auto child = parseStatement();

//    while (stmtToken.type != TokenType::RIGHT_CURLY_BRACKET) {
//        auto childNode = parseStatement();
//        if (childNode.children.size() < 1) {
//            cerr << "empty SIMPLE Programme with no statement received" << endl;
//            return static_cast<TNode>(static_cast<TokenType>(NULL));
//        }
//        node.children.push_back(childNode);
//        stmtToken = tokenList[pos];
//    }
//    ++ pos;

    node.children.push_back(child);
    ++ pos;
    return node;
}

TNode Parser::parseStatement() {
    if (pos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token currToken = tokenList[pos];
    TNode stmtNode;
    stmtNode.nodeType = TokenType::STATEMENT_LIST;
    int checkerPos = pos - 2;
    if (tokenList[checkerPos].type == TokenType::IF &&
    (tokenList[checkerPos].value == "then" || tokenList[checkerPos].value == "else")) {
        stmtNode.stringId = tokenList[checkerPos].value;
    } else {
        stmtNode.stringId = "stmtList";
    }
    stmtNode.stmtNumber = currToken.lineNumber;
    while (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        currToken = tokenList[pos];
        if (currToken.type == TokenType::READ) {
            auto childNode = parseReadStatement();
            stmtNode.children.push_back(childNode);
            //return stmtNode;
        }
        if (currToken.type == TokenType::PRINT) {
            auto childNode = parsePrintStatement();
            stmtNode.children.push_back(childNode);
            //return stmtNode;
        }
        if (currToken.type == TokenType::WHILE) {
            auto childNode = parseWhileStatement();
            stmtNode.children.push_back(childNode);
        }
        if (currToken.type == TokenType::IF) {
            auto childNode = parseIfStatement();
            stmtNode.children.push_back(childNode);
        }
        if (currToken.type == TokenType::NAME_IDENTIFIER) {
            auto childNode = parseAssignStatement();
            stmtNode.children.push_back(childNode);
        }
    }
    return stmtNode;
}

TNode Parser::parseAssignStatement() {
    Token currToken = tokenList[pos];
    TNode assignNode;
    assignNode.nodeType = TokenType::ASSIGN;
    assignNode.stringId = "assign";
    assignNode.stmtNumber = currToken.lineNumber;
    //lhs, var Node
    TNode lhs = constructVarNode(currToken);
    assignNode.children.push_back(lhs);
    Token assignOperator = tokenList[++ pos];
    if (assignOperator.type != TokenType::OPERATOR || assignOperator.value != "=") {
        cerr << "Expected '=' sign for the assignment statement but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    //rhs, expr Node
    ++ pos;
    auto rhs = parseExpression();
    assignNode.children.push_back(rhs);
    Token following = tokenList[pos];
    if (following.type != TokenType::STATEMENT_TERMINAL) {
        cerr << "Expected statement terminal ';' but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    return assignNode;
}

TNode Parser::constructVarNode(const Token& token) {
    TNode varNode;
    varNode.nodeType = token.type;
    varNode.stringId = token.value;
    varNode.stmtNumber = token.lineNumber;
    return varNode;
}

TNode Parser::parseExpression() {
    auto node = parseTerm();
    while (tokenList[pos].type == TokenType::OPERATOR && (tokenList[pos].value == "+" || tokenList[pos].value == "-")) {
        Token currToken = tokenList[pos];
        TNode opNode;
        opNode.nodeType = currToken.type;
        opNode.stringId = currToken.value;
        opNode.stmtNumber = currToken.lineNumber;
        opNode.children.push_back(node);
        ++ pos;
        opNode.children.push_back(parseTerm());
        node = opNode;
    }
    return node;
}

TNode Parser::parseTerm() {
    auto node = parseFactor();

    while (tokenList[pos].type == TokenType::OPERATOR &&
    (tokenList[pos].value == "*" || tokenList[pos].value == "/" || tokenList[pos].value == "%")) {
        Token currToken = tokenList[pos];
        TNode termNode;
        termNode.nodeType = TokenType::OPERATOR;
        termNode.stringId = currToken.value;
        termNode.stmtNumber = currToken.lineNumber;
        termNode.children.push_back(node);
        ++ pos;
        termNode.children.push_back(parseFactor());
        node = termNode;
    }
    return node;
}

TNode Parser::parseFactor() {
    TNode node;
    Token currToken = tokenList[pos];
    if (currToken.type == TokenType::LEFT_ROUND_BRACKET) {
        ++ pos;
        node = parseExpression();
        currToken = tokenList[pos];
        if (currToken.type != TokenType::RIGHT_ROUND_BRACKET) {
            cerr << "Expected closing bracket ')' but instead got: " << currToken.value << endl;
            return static_cast<TNode>(static_cast<TokenType>(NULL));
        }
        return node;
    }
    if (currToken.type == TokenType::NAME_IDENTIFIER) {
        node = constructVarNode(currToken);
        ++ pos;
    }
    else {
        node.nodeType = currToken.type;
        node.stringId = currToken.value;
        node.stmtNumber = currToken.lineNumber;
    }
    return node;
}

TNode Parser::parseIfStatement() {
    TNode ifNode;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "if")) {
        cerr << "Expected 'if' keyword but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ifNode.nodeType = TokenType::IF;
    ifNode.stringId = tokenList[pos].value;
    ifNode.stmtNumber = tokenList[pos].lineNumber;
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
        cerr << "Expected '(' after 'if' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    TNode condChild = parseConditionalExpr();
    if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        cerr << "Expected ')' after cond_expr of 'if' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "then")) {
        cerr << "Expected 'then' keyword after (cond_expr) of 'if' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cerr << "Expected '{' keyword after 'then' keyword of 'if' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    TNode thenBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cerr << "Expected '}' keyword after stmtList of 'then' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "else")) {
        cerr << "Expected 'else' keyword after '}' of 'then' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cerr << "Expected '{' keyword after 'else' keyword of 'if' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    TNode elseBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cerr << "Expected '}' keyword after stmtList of 'else' but instead got: " << tokenList[pos].value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ifNode.children.push_back(condChild);
    ifNode.children.push_back(thenBody);
    ifNode.children.push_back(elseBody);
    return ifNode;
}

TNode Parser::parseWhileStatement() {
    Token currToken = tokenList[pos];
    TNode whileNode;
    whileNode.nodeType = currToken.type;
    whileNode.stringId = currToken.value;
    whileNode.stmtNumber = currToken.lineNumber;
    if (currToken.type != TokenType::WHILE) {
        cerr << "Expected 'while' keyword for the statement but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token next = tokenList[++ pos];
    if (next.type != TokenType::LEFT_ROUND_BRACKET) {
        cerr << "Expected '(' after while keyword but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    TNode condChild = parseConditionalExpr();
    if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        cerr << "Expected ')' after conditional expr in 'while' but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }

    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cerr << "Expected '{' after conditional expr in 'while' but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    TNode whileBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cerr << "Expected '}' after stmtList in 'while' but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++ pos;
    whileNode.children.push_back(condChild);
    whileNode.children.push_back(whileBody);
    return whileNode;
}

TNode Parser::parseConditionalExpr() {
    Token currToken = tokenList[pos];
    TNode condNode;
    if (currToken.type == TokenType::OPERATOR && currToken.value == "!") {
        condNode.nodeType = currToken.type;
        condNode.stringId = "neg";
        condNode.stmtNumber = currToken.lineNumber;
        ++ pos;
        if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
            cerr << "Expected '(' after negation sign '!' but instead got: " << currToken.value << endl;
            return static_cast<TNode>(static_cast<TokenType>(NULL));
        }
        ++ pos;
        condNode.children.push_back(parseConditionalExpr());
        if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cerr << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
            return static_cast<TNode>(static_cast<TokenType>(NULL));
        }
        return condNode;
    } else if (currToken.type == TokenType::LEFT_ROUND_BRACKET) {
        ++ pos;
        condNode = parseConditionalExpr();
        if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cerr << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
            return static_cast<TNode>(static_cast<TokenType>(NULL));
        }
        ++ pos;
        if (tokenList[pos].type == TokenType::OPERATOR && tokenList[pos].value == "&&") {
            TNode andNode;
            andNode.nodeType = TokenType::OPERATOR;
            andNode.stringId = "and";
            andNode.stmtNumber = tokenList[pos].lineNumber;
            ++ pos;
            if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
                cerr << "Expected '(' after '&&' operator but instead got: " << currToken.value << endl;
                return static_cast<TNode>(static_cast<TokenType>(NULL));
            }
            andNode.children.push_back(condNode);
            ++ pos;
            andNode.children.push_back(parseConditionalExpr());
            if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cerr << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
                return static_cast<TNode>(static_cast<TokenType>(NULL));
            }
            return andNode;
        } else {
            if (tokenList[pos].value != "||") {
                cerr << "Expected '&&' or '||' operator but instead got: " << currToken.value << endl;
                return static_cast<TNode>(static_cast<TokenType>(NULL));
            }
            TNode orNode;
            orNode.nodeType = TokenType::OPERATOR;
            orNode.stringId = "or";
            orNode.stmtNumber = tokenList[pos].lineNumber;
            ++ pos;
            if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
                cerr << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
                return static_cast<TNode>(static_cast<TokenType>(NULL));
            }
            orNode.children.push_back(condNode);
            ++ pos;
            orNode.children.push_back(parseConditionalExpr());
            if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cerr << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
                return static_cast<TNode>(static_cast<TokenType>(NULL));
            }
            return orNode;
        }
    } else {
        return parseRelationalExpr();
    }
}

TNode Parser::parseRelationalExpr() {
    TNode node = parseRelationalFactor();
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

TNode Parser::parseRelationalFactor() {
    TNode node;
    Token currToken = tokenList[pos];
    if (currToken.type == TokenType::NAME_IDENTIFIER || currToken.type == TokenType::INTEGER) {
        node = constructVarNode(currToken);
        ++ pos;
    } else {
        if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
            cerr << "Expected '(' for a relational expr but instead got: " << currToken.value << endl;
            return static_cast<TNode>(static_cast<TokenType>(NULL));
        }
        ++ pos;
        node = parseExpression();
        if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
            cerr << "Expected '(' for a relational expr but instead got: " << currToken.value << endl;
            return static_cast<TNode>(static_cast<TokenType>(NULL));
        }
    }
    return node;
}

TNode Parser::parsePrintStatement() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = currToken.type;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::READ) {
        cerr << "Expected print keyword for the statement but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    int checkerPos = pos + 2;
    if (checkerPos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after print keyword, with no ';' " << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        cerr << "Expected stmt terminal ';' after variable name, but got " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }

    Token varNameToken = tokenList[++pos];
    TNode child;
    child.nodeType = varNameToken.type;
    child.stringId = varNameToken.value;
    child.stmtNumber = varNameToken.lineNumber;
    node.children.push_back(child);
    pos += 2;
    return node;
}

TNode Parser::parseReadStatement() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = currToken.type;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::READ) {
        cerr << "Expected read keyword for the statement but instead got: " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    int checkerPos = pos + 2;
    if (checkerPos >= tokenList.size()) {
        cerr << "SIMPLE source end unexpectedly after read keyword, with no stmt terminal" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        cerr << "Expected stmt terminal ';' after variable name, but got " << currToken.value << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token varNameToken = tokenList[++pos];
    TNode childNode;
    childNode.nodeType = varNameToken.type;
    childNode.stringId = varNameToken.value;
    childNode.stmtNumber = varNameToken.lineNumber;
    // increment pos by 2 because we have verified the existence of statement terminal ';'
    pos += 2;
    node.children.push_back(childNode);
    return node;
}

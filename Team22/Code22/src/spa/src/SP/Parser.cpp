#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <utility>
#include <stdexcept>

using namespace std;
#include "Parser.h"
#include "TNode.h"

TNode Parser::Parse() {
    Token currToken = tokenList[pos];
    ++pos;
    if (currToken.type != TokenType::PROCEDURE) {
        cout << "Expecting keyword procedure for a legal SIMPLE program" << endl;
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
        cout << "Expecting function name for a procedure, got something else" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++pos;
    if (pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after a procedure name" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token nextToken = tokenList[pos];
    if (nextToken.type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expecting '{' after procedure name declaration but got:" << nextToken.value <<endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    ++pos;
    if (pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token stmtToken = tokenList[pos];
    // Recursion should happen in the stmtList node
    auto child = parseStatement();

//    while (stmtToken.type != TokenType::RIGHT_CURLY_BRACKET) {
//        auto childNode = parseStatement();
//        if (childNode.children.size() < 1) {
//            cout << "empty SIMPLE Programme with no statement received" << endl;
//            return static_cast<TNode>(static_cast<TokenType>(NULL));
//        }
//        node.children.push_back(childNode);
//        stmtToken = tokenList[pos];
//    }
//    ++ pos;

    node.children.push_back(child);
    //++ pos;
    return node;
}

TNode Parser::parseStatement() {
    if (pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        return static_cast<TNode>(static_cast<TokenType>(NULL));
    }
    Token currToken = tokenList[pos];
    TNode stmtNode;
    stmtNode.nodeType = TokenType::STATEMENT_LIST;
    int checkerPos = pos - 2;
    if (tokenList[checkerPos].type == TokenType::IF &&
    (tokenList[checkerPos].value == "then" || tokenList[checkerPos].value == "else")) {
        stmtNode.stringId = tokenList[checkerPos].value;
        stmtNode.stmtNumber = tokenList[checkerPos].lineNumber;
    } else {
        stmtNode.stringId = "stmtList";
        stmtNode.stmtNumber = currToken.lineNumber;
    }
    while (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        //currToken = tokenList[pos];
        if (tokenList[pos].type == TokenType::READ) {
            auto childNode = parseReadStatement();
            stmtNode.children.push_back(childNode);
            //return stmtNode;
        }
        if (tokenList[pos].type == TokenType::PRINT) {
            auto childNode = parsePrintStatement();
            stmtNode.children.push_back(childNode);
            //return stmtNode;
        }
        if (tokenList[pos].type == TokenType::WHILE) {
            auto childNode = parseWhileStatement();
            stmtNode.children.push_back(childNode);
        }
        if (tokenList[pos].type == TokenType::IF) {
            auto childNode = parseIfStatement();
            stmtNode.children.push_back(childNode);
        }
        if (tokenList[pos].type == TokenType::NAME_IDENTIFIER) {
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
        cout << "Expected '=' sign for the assignment statement but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    //rhs, expr Node
    ++ pos;
    auto rhs = parseExpression();
    assignNode.children.push_back(rhs);
    Token following = tokenList[pos];
    if (following.type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected statement terminal ';' but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
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
            cout << "Expected closing bracket ')' but instead got: " << currToken.value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
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
        ++ pos;
    }
    return node;
}

TNode Parser::parseIfStatement() {
    TNode ifNode;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "if")) {
        cout << "Expected 'if' keyword but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ifNode.nodeType = TokenType::IF;
    ifNode.stringId = tokenList[pos].value;
    ifNode.stmtNumber = tokenList[pos].lineNumber;
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
        cout << "Expected '(' after 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode condChild = parseConditionalExpr();
    if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        cout << "Expected ')' after cond_expr of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "then")) {
        cout << "Expected 'then' keyword after (cond_expr) of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expected '{' keyword after 'then' keyword of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode thenBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' keyword after stmtList of 'then' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (!(tokenList[pos].type == TokenType::IF && tokenList[pos].value == "else")) {
        cout << "Expected 'else' keyword after '}' of 'then' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expected '{' keyword after 'else' keyword of 'if' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode elseBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' keyword after stmtList of 'else' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
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
        cout << "Expected 'while' keyword for the statement but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token next = tokenList[++ pos];
    if (next.type != TokenType::LEFT_ROUND_BRACKET) {
        cout << "Expected '(' after while keyword but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode condChild = parseConditionalExpr();
    if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        cout << "Expected ')' after conditional expr in 'while' but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }

    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expected '{' after conditional expr in 'while' but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode whileBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' after stmtList in 'while' but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    whileNode.children.push_back(condChild);
    whileNode.children.push_back(whileBody);
    return whileNode;
}

TNode Parser::parseConditionalExpr() {
    Token currToken = tokenList[pos];
    TNode condNode;
    if (tokenList[pos].type == TokenType::OPERATOR && currToken.value == "!") {
        condNode.nodeType = currToken.type;
        condNode.stringId = "neg";
        condNode.stmtNumber = currToken.lineNumber;
        ++ pos;
        if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
            cout << "Expected '(' after negation sign '!' but instead got: " << currToken.value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ pos;
        condNode.children.push_back(parseConditionalExpr());
        if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cout << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ pos;
        return condNode;
    } else if (tokenList[pos].type == TokenType::LEFT_ROUND_BRACKET) {
        ++ pos;
        condNode = parseConditionalExpr();
        if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cout << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ pos;
        if (tokenList[pos].type == TokenType::OPERATOR && tokenList[pos].value == "&&") {
            TNode andNode;
            andNode.nodeType = TokenType::OPERATOR;
            andNode.stringId = "and";
            andNode.stmtNumber = tokenList[pos].lineNumber;
            ++ pos;
            if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
                cout << "Expected '(' after '&&' operator but instead got: " << currToken.value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            andNode.children.push_back(condNode);
            ++ pos;
            andNode.children.push_back(parseConditionalExpr());
            if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++ pos;
            return andNode;
        } else {
            if (tokenList[pos].value != "||") {
                cout << "Expected '&&' or '||' operator but instead got: " << currToken.value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            TNode orNode;
            orNode.nodeType = TokenType::OPERATOR;
            orNode.stringId = "or";
            orNode.stmtNumber = tokenList[pos].lineNumber;
            ++ pos;
            if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            orNode.children.push_back(condNode);
            ++ pos;
            orNode.children.push_back(parseConditionalExpr());
            if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << currToken.value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++ pos;
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
            cout << "Expected '(' for a relational expr but instead got: " << currToken.value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ pos;
        node = parseExpression();
        if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cout << "Expected ')' for a relational expr but instead got: " << currToken.value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ pos;
    }
    return node;
}

TNode Parser::parsePrintStatement() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = currToken.type;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;

    if (currToken.type != TokenType::PRINT) {
        cout << "Expected print keyword for the statement but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    int checkerPos = pos + 2;
    if (checkerPos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after print keyword, with no ';' " << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected stmt terminal ';' after variable name, but got " << pendingCheckTerminalToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
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
        cout << "Expected read keyword for the statement but instead got: " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    int checkerPos = pos + 2;
    if (checkerPos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after read keyword, with no stmt terminal" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token pendingCheckTerminalToken = tokenList[checkerPos];
    if (pendingCheckTerminalToken.type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected stmt terminal ';' after variable name, but got " << currToken.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
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

//int main() {
//    vector<Token> tokens;
//    tokens.push_back(Token(TokenType::PROCEDURE, "procedure", 0));
//    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "compute", 0));
//    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 0));
//    //base test 1 read and print
////    tokens.push_back(Token(TokenType::READ, "read", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "x", 1));
////    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 1));
////    tokens.push_back(Token(TokenType::PRINT, "print", 2));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 2));
////    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
//    //base test 2 assignment stmt
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "normsq", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "=", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centX", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "*", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centX", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "+", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centY", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "*", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centY", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "-", 1));
////    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
////    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 1));
//    //base test 3 while stmt
////    tokens.push_back(Token(TokenType::WHILE, "while", 1));
////    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
////    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "x", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "!=", 1));
////    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
////    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "&&", 1));
////    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 1));
////    tokens.push_back(Token(TokenType::OPERATOR, "!=", 1));
////    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
////    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
////    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
////    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 1));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "centX", 2));
////    tokens.push_back(Token(TokenType::OPERATOR, "=", 2));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "a", 2));
////    tokens.push_back(Token(TokenType::OPERATOR, "/", 2));
////    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "b", 2));
////    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
////    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
//    //base test 4 if stmt
//    tokens.push_back(Token(TokenType::IF, "if", 1));
//    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
//    tokens.push_back(Token(TokenType::OPERATOR, "!", 1));
//    tokens.push_back(Token(TokenType::LEFT_ROUND_BRACKET, "(", 1));
//    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 1));
//    tokens.push_back(Token(TokenType::OPERATOR, ">", 1));
//    tokens.push_back(Token(TokenType::INTEGER, "1", 1));
//    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
//    tokens.push_back(Token(TokenType::RIGHT_ROUND_BRACKET, ")", 1));
//    tokens.push_back(Token(TokenType::IF, "then", 1));
//    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 1));
//    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 2));
//    tokens.push_back(Token(TokenType::OPERATOR, "=", 2));
//    tokens.push_back(Token(TokenType::INTEGER, "1", 2));
//    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 2));
//    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 2));
//    tokens.push_back(Token(TokenType::IF, "else", 1));
//    tokens.push_back(Token(TokenType::LEFT_CURLY_BRACKET, "{", 2));
//    tokens.push_back(Token(TokenType::NAME_IDENTIFIER, "y", 3));
//    tokens.push_back(Token(TokenType::OPERATOR, "=", 3));
//    tokens.push_back(Token(TokenType::INTEGER, "2", 3));
//    tokens.push_back(Token(TokenType::STATEMENT_TERMINAL, ";", 3));
//    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 3));
//    tokens.push_back(Token(TokenType::RIGHT_CURLY_BRACKET, "}", 3));
//    for (Token token: tokens) {
//            std::cout << "Token" << ToString(token) << std::endl;
//    }
//    Parser parser = Parser(tokens);
//    TNode result;
//    try {
//        result = parser.Parse();
//    } catch (std::invalid_argument& e) {
//        std::cerr << e.what() << endl;
//        ::exit(1);
//    }
//
//    if (result.children.empty()) {
//        cout << "Null pointer returned, use debug mode to find out why" << endl;
//    }
//    std::queue<TNode> pendingToString;
//    pendingToString.push(result);
//    while (!pendingToString.empty()) {
//        auto toProcess = pendingToString.front();
//        pendingToString.pop();
//        cout << ToString(toProcess) << endl;
//        if (!toProcess.children.empty()) {
//            auto childrenArr = (toProcess).children;
//            for (TNode child: childrenArr) {
//                pendingToString.push(child);
//            }
//        }
//    }
//    return 0;
//};
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

/**
 * Entry point of parsing. Handles multiple procedures.
 *
 * @return an AST representation of the SIMPLE Source
 */
TNode Parser::Parse() {
    Token currToken = tokenList[pos];
    if (currToken.type != TokenType::PROCEDURE) {
        cout << "Expecting keyword procedure for a legal SIMPLE program" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    TNode programNode;
    programNode.nodeType = TokenType::PROGRAM;
    programNode.stringId = currToken.value;
    programNode.stmtNumber = currToken.lineNumber;
    //++ pos;
    while (tokenList[pos].type == TokenType::PROCEDURE) {
        programNode.children.push_back(parseProcedure());
    }
    if (pos != tokenList.size()) {
        cout << "Tangling tokens outside the last procedure are ignored" << endl;
    }
    return programNode;
}

/**
 * Parse one single procedure of a SIMPLE Source.
 *
 * @return an AST representation of a procedure
 */
TNode Parser::parseProcedure() {
    Token currToken = tokenList[pos];
    TNode node;
    node.nodeType = TokenType::PROCEDURE;
    node.stringId = currToken.value;
    node.stmtNumber = currToken.lineNumber;
    ++ pos;
    if (tokenList[pos].type != TokenType::NAME_IDENTIFIER) {
        cout << "Expecting function name for a procedure, got something else" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after a procedure name" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token nextToken = tokenList[pos];
    if (nextToken.type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expecting '{' after procedure name declaration but got:" << nextToken.value <<endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    if (pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    Token stmtToken = tokenList[pos];
    // Recursion happens in the stmtList node
    auto child = parseStatement();
    node.children.push_back(child);
    if (pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly without right curly bracket" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' at the end of a procedure but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
     ++ pos;
    return node;
}

/**
 * Parse the 'stmtList', which is a block containing one or more statements.
 *
 * @return an AST representing a Statement List block
 */
TNode Parser::parseStatement() {
    if (pos >= tokenList.size()) {
        cout << "SIMPLE source end unexpectedly after left curly bracket" << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
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
    while (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET && pos < tokenList.size()) {
        if (pos >= tokenList.size()) {
            cout << "SIMPLE source procedure ends unexpectedly without right curly bracket" << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        if (tokenList[pos].type == TokenType::READ) {
            auto childNode = parseReadStatement();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[pos].type == TokenType::PRINT) {
            auto childNode = parsePrintStatement();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[pos].type == TokenType::WHILE) {
            auto childNode = parseWhileStatement();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[pos].type == TokenType::IF) {
            auto childNode = parseIfStatement();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[pos].type == TokenType::NAME_IDENTIFIER) {
            auto childNode = parseAssignStatement();
            stmtNode.children.push_back(childNode);
        }
        else if (tokenList[pos].type == TokenType::CALL) {
            auto childNode = parseCallStatement();
            stmtNode.children.push_back(childNode);
        }
        else {
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Unrecognized Token");
        }
    }
    return stmtNode;
}

/**
 * Parse one single call statement. The string Id of the call node records the procedure being called.
 *
 * @return
 */
TNode Parser::parseCallStatement() {
    Token currToken = tokenList[pos];
    ++ pos;
    TNode callNode;
    callNode.nodeType = TokenType::CALL;
    callNode.stmtNumber = currToken.lineNumber;
    if (tokenList[pos].type != TokenType::NAME_IDENTIFIER) {
        cout << "Expected procedure name for a CALL stmt but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    callNode.stringId = tokenList[pos].value;
    ++ pos;
    if (tokenList[pos].type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected statement terminal ';' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    return callNode;
}

/**
 * Parse one single assignment statement with exactly two children, left-hand side and right-hand side.
 *
 * @return an AST representation of one single assignment statement
 */
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
        cout << "Expected '=' sign for the assignment statement but instead got: " << assignOperator.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    //rhs, expr Node
    ++ pos;
    auto rhs = parseExpression();
    assignNode.children.push_back(rhs);
    Token following = tokenList[pos];
    if (following.type != TokenType::STATEMENT_TERMINAL) {
        cout << "Expected statement terminal ';' but instead got: " << following.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    return assignNode;
}

/**
 * Build a variable Tree Node with the Token given.
 *
 * @param token a Token of Type NAME_IDENTIFIER
 * @return a TNode representation of the variable
 */
TNode Parser::constructVarNode(const Token& token) {
    TNode varNode;
    varNode.nodeType = token.type;
    varNode.stringId = token.value;
    varNode.stmtNumber = token.lineNumber;
    return varNode;
}

/**
 * Parse the 'expr' of SIMPLE Source.
 *
 * @return an AST representation of an expression
 */
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

/**
 * Parse the 'term' of SIMPLE Source.
 *
 * @return an AST representation of a term
 */
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

/**
 * Parse the 'factor' of SIMPLE Source.
 *
 * @return an AST representation of a factor
 */
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
        ++ pos;
        return node;
    }
    if (currToken.type == TokenType::NAME_IDENTIFIER) {
        node = constructVarNode(currToken);
        ++ pos;
    }
    else {
        if (currToken.type != TokenType::INTEGER) {
            cout << "Expected constant or variable but instead got: " << currToken.value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        node.nodeType = currToken.type;
        node.stringId = currToken.value;
        node.stmtNumber = currToken.lineNumber;
        ++ pos;
    }
    return node;
}

/**
 * Parse one single If statement, which has exactly three children of condition, then stmtList and else stmtList.
 *
 * @return an AST representation of one single If statement
 */
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

/**
 * Parse one single While statement, which has exactly two children of condition, and a stmtList.
 *
 * @return an AST representation of one single While statement
 */
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
        cout << "Expected '(' after while keyword but instead got: " << next.value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode condChild = parseConditionalExpr();
    if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
        cout << "Expected ')' after conditional expr in 'while' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }

    ++ pos;
    if (tokenList[pos].type != TokenType::LEFT_CURLY_BRACKET) {
        cout << "Expected '{' after conditional expr in 'while' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    TNode whileBody = parseStatement();
    if (tokenList[pos].type != TokenType::RIGHT_CURLY_BRACKET) {
        cout << "Expected '}' after stmtList in 'while' but instead got: " << tokenList[pos].value << endl;
        throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
    }
    ++ pos;
    whileNode.children.push_back(condChild);
    whileNode.children.push_back(whileBody);
    return whileNode;
}

/**
 * Parse the 'cond_expr' of SIMPLE Source.
 *
 * @return an AST representation of a conditional expression
 */
TNode Parser::parseConditionalExpr() {
    Token currToken = tokenList[pos];
    TNode condNode;
    if (tokenList[pos].type == TokenType::OPERATOR && currToken.value == "!") {
        condNode.nodeType = currToken.type;
        condNode.stringId = "neg";
        condNode.stmtNumber = currToken.lineNumber;
        ++ pos;
        if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
            cout << "Expected '(' after negation sign '!' but instead got: " << tokenList[pos].value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ pos;
        condNode.children.push_back(parseConditionalExpr());
        if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
            throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
        }
        ++ pos;
        return condNode;
    } else if (tokenList[pos].type == TokenType::LEFT_ROUND_BRACKET) {
        // find matching right round bracket and check if it is && or || operator
        // Token followingRightRoundBracket = Token(UNKNOWN, "unknown", -1);
        int recorder = -1;
        int stack = 0;
        bool flag = false;
        for (int i = pos; i < tokenList.size(); i++ ) {
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
        ++ pos;
        condNode = parseConditionalExpr();
        if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
            cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
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
                cout << "Expected '(' after '&&' operator but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            andNode.children.push_back(condNode);
            ++ pos;
            andNode.children.push_back(parseConditionalExpr());
            if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++ pos;
            return andNode;
        } else {
            if (tokenList[pos].value != "||") {
                cout << "Expected '&&' or '||' operator but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            TNode orNode;
            orNode.nodeType = TokenType::OPERATOR;
            orNode.stringId = "or";
            orNode.stmtNumber = tokenList[pos].lineNumber;
            ++ pos;
            if (tokenList[pos].type != TokenType::LEFT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            orNode.children.push_back(condNode);
            ++ pos;
            orNode.children.push_back(parseConditionalExpr());
            if (tokenList[pos].type != TokenType::RIGHT_ROUND_BRACKET) {
                cout << "Expected ')' after a conditional expr but instead got: " << tokenList[pos].value << endl;
                throw std::invalid_argument("Illegal SIMPLE Source Programme: Syntax error");
            }
            ++ pos;
            return orNode;
        }
    } else {
        return parseRelationalExpr();
    }
}

/**
 * Parse the 'rel_expr' of SIMPLE Source.
 *
 * @return an AST representation of a relational expression
 */
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

/**
 * Parse the 'rel_factor' of SIMPLE Source.
 *
 * @return an AST representation of a relational factor
 */
TNode Parser::parseRelationalFactor() {
    TNode node;
    Token currToken = tokenList[pos];
    if (currToken.type == TokenType::NAME_IDENTIFIER || currToken.type == TokenType::INTEGER) {
        int peekPos = pos + 1;
        if (tokenList[peekPos].type == TokenType::RIGHT_ROUND_BRACKET ||
        (tokenList[peekPos].type == TokenType::OPERATOR && (tokenList[peekPos].value == ">" ||
        tokenList[peekPos].value == ">="|| tokenList[peekPos].value == "<=" ||tokenList[peekPos].value == "<"
        || tokenList[peekPos].value == "==" || tokenList[peekPos].value == "!="))) {
            node = constructVarNode(currToken);
            ++pos;
        }
        else {
            node = parseExpression();
        }
    } else {
        node = parseExpression();
    }
    return node;
}

/**
 * Parse one single print statement, which has exactly one child.
 *
 * @return an AST representation of the print statement
 */
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

/**
 * Parse one single read statement, which has exactly one child.
 *
 * @return an AST representation of the print statement
 */
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
        cout << "Expected stmt terminal ';' after variable name, but got " << pendingCheckTerminalToken.value << endl;
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

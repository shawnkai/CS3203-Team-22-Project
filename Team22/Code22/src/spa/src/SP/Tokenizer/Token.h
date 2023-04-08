#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

#endif//SPA_TOKEN_H
#pragma once
#include <string>
#include <utility>

enum TokenType {
    NAME_IDENTIFIER,// ost, wes... variable names and procedure name
    PROCEDURE,
    PROGRAM,
    READ,
    PRINT,
    ASSIGN,
    WHILE,
    IF,
    CALL,
    INTEGER,           // 1, 2, 0, ...
    OPERATOR,          // >, >=, <, <=, =, !=, ==, &&, ||, !, +, -, *, /, %
    STATEMENT_TERMINAL,// ;
    STATEMENT_LIST,
    LEFT_ROUND_BRACKET,
    RIGHT_ROUND_BRACKET,
    LEFT_CURLY_BRACKET,
    RIGHT_CURLY_BRACKET,
    CONDITIONAL_EXPR,
    EXPR,
    FACTOR,
    RELATIONAL_EXPR,
    RELATIONAL_FACTOR,
    TERM,
    UNKNOWN
};

inline const char *ToString(TokenType t) {
    switch (t) {
        case NAME_IDENTIFIER:
            return "NAME_IDENTIFIER";
        case PROCEDURE:
            return "PROCEDURE";
        case PROGRAM:
            return "PROGRAM";
        case READ:
            return "READ";
        case PRINT:
            return "PRINT";
        case ASSIGN:
            return "ASSIGNMENT";
        case WHILE:
            return "WHILE";
        case IF:
            return "IF";
        case CALL:
            return "CALL";
        case INTEGER:
            return "INTEGER";
        case OPERATOR:
            return "OPERATOR";
        case STATEMENT_TERMINAL:
            return "STATEMENT_TERMINAL";
        case STATEMENT_LIST:
            return "STATEMENT_LIST";
        case LEFT_ROUND_BRACKET:
            return "LEFT_ROUND_BRACKET";
        case RIGHT_ROUND_BRACKET:
            return "RIGHT_ROUND_BRACKET";
        case LEFT_CURLY_BRACKET:
            return "LEFT_CURLY_BRACKET";
        case RIGHT_CURLY_BRACKET:
            return "RIGHT_CURLY_BRACKET";
        case CONDITIONAL_EXPR:
            return "CONDITIONAL_EXPR";
        case EXPR:
            return "EXPR";
        case RELATIONAL_EXPR:
            return "RELATIONAL_EXPR";
        case RELATIONAL_FACTOR:
            return "RELATIONAL_FACTOR";
        case TERM:
            return "TERM";
        case FACTOR:
            return "FACTOR";
        default:
            return "UNKNOWN_TOKEN_TYPE";
    }
}

inline int ToIntegral(TokenType t) {
    switch (t) {
        case PROGRAM:
            return 1;
        case PROCEDURE:
            return 2;
        case STATEMENT_LIST:
            return 3;
        case IF:
            return 4;
        case WHILE:
            return 5;
        case ASSIGN:
            return 6;
        case CALL:
            return 7;
        case PRINT:
            return 8;
        case READ:
            return 9;
        case CONDITIONAL_EXPR:
            return 10;
        case RELATIONAL_EXPR:
            return 11;
        case RELATIONAL_FACTOR:
            return 12;
        case EXPR:
            return 13;
        case TERM:
            return 14;
        case FACTOR:
            return 15;
        case NAME_IDENTIFIER:
            return 16;
        case INTEGER:
            return 17;
        default:
            return 999;
    }
}

inline TokenType getTypeFromKeywordToken(const std::string& candidate) {
    if (candidate == "procedure") {
        return PROCEDURE;
    } else if (candidate == "read") {
        return READ;
    } else if (candidate == "print") {
        return PRINT;
    } else if (candidate == "while") {
        return WHILE;
    } else if (candidate == "if" || candidate == "then" || candidate == "else") {
        return IF;
    } else if (candidate == "call") {
        return CALL;
    } else {
        throw std::invalid_argument("not a keyword for SIMPLE source");
    }
}

struct Token {
    TokenType type;
    std::string value;
    int lineNumber;

    Token(TokenType tokenType, std::string tokenValue, int lineNum) : type(tokenType), value(std::move(tokenValue)),
                                                                      lineNumber(lineNum) {}
};

inline std::string ToString(const Token &t) {
    return ToString(t.type) + t.value + std::to_string(t.lineNumber);
}

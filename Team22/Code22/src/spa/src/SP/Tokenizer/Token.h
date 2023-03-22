#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

#endif //SPA_TOKEN_H
#pragma once
#include <string>
#include <utility>

enum TokenType {
    NAME_IDENTIFIER, // ost, wes... variable names and procedure name
    PROCEDURE,
    PROGRAM,
    READ,
    PRINT,
    ASSIGN,
    WHILE,
    IF,
    CALL,
    INTEGER, // 1, 2, 0, ...
    OPERATOR, // >, >=, <, <=, =, !=, ==, &&, ||, !, +, -, *, /, %
    STATEMENT_TERMINAL, // ;
    STATEMENT_LIST,
    LEFT_ROUND_BRACKET,
    RIGHT_ROUND_BRACKET,
    LEFT_CURLY_BRACKET,
    RIGHT_CURLY_BRACKET,
    UNKNOWN
};

inline const char* ToString(TokenType t) {
    switch (t) {
        case NAME_IDENTIFIER: return "NAME_IDENTIFIER";
        case PROCEDURE: return "PROCEDURE";
        case PROGRAM: return "PROGRAM";
        case READ: return "READ";
        case PRINT: return "PRINT";
        case ASSIGN: return "ASSIGNMENT";
        case WHILE: return "WHILE";
        case IF: return "IF";
        case CALL: return "CALL";
        case INTEGER: return "INTEGER";
        case OPERATOR: return "OPERATOR";
        case STATEMENT_TERMINAL: return "STATEMENT_TERMINAL";
        case STATEMENT_LIST: return "STATEMENT_LIST";
        case LEFT_ROUND_BRACKET: return "LEFT_ROUND_BRACKET";
        case RIGHT_ROUND_BRACKET: return "RIGHT_ROUND_BRACKET";
        case LEFT_CURLY_BRACKET: return "LEFT_CURLY_BRACKET";
        case RIGHT_CURLY_BRACKET: return "RIGHT_CURLY_BRACKET";
        default: return "UNKNOWN_TOKEN_TYPE";
    }
}

struct Token {
    TokenType type;
    std::string value;
    int lineNumber;

    Token(TokenType tokenType, std::string tokenValue, int lineNum) : type(tokenType), value(std::move(tokenValue)),
    lineNumber(lineNum) {}

};

inline std::string ToString(const Token& t) {
    return ToString(t.type) + t.value + std::to_string(t.lineNumber);
}

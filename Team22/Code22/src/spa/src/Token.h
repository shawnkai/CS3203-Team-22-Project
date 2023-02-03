#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

#endif //SPA_TOKEN_H
#pragma once
#include <string>
#include <utility>

enum TokenType {
    NAME_IDENTIFIER, // ost, wes... variable names
    PROCEDURE, //read, (for now) if, while, assign ...
    READ,
    INTEGER, // 1, 2, 0, ...
    OPERATOR, // >, >=, <, <=, =, ... (not for now)
    STATEMENT_TERMINAL, // ;
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
        case READ: return "READ";
        case STATEMENT_TERMINAL: return "STATEMENT_TERMINAL";
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

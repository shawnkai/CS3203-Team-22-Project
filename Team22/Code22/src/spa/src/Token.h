#ifndef SPA_TOKEN_H
#define SPA_TOKEN_H

#endif //SPA_TOKEN_H

#include <string>
#include <utility>

enum TokenType {
    NAME_IDENTIFIER, // ost, wes... variable names
    PROCEDURE, //read, (for now) if, while, assign ...
    READ,
    INTEGER, // 1, 2, 0, ...
    OPERATOR, // >, >=, <, <=, =, ... (not for now)
    STATEMENT_TERMINAL,
    LEFT_ROUND_BRACKET,
    RIGHT_ROUND_BRACKET,
    LEFT_CURLY_BRACKET,
    RIGHT_CURLY_BRACKET
};

struct Token {
    TokenType type;
    std::string value;
    int lineNumber;

    Token(TokenType tokenType, std::string tokenValue, int lineNum) : type(tokenType), value(std::move(tokenValue)),
    lineNumber(lineNum) {}
};

#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#endif //SPA_TOKENIZER_H
#pragma once
#include "Token.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include "Token.h"

class Tokenizer {
public:
    explicit Tokenizer() : prevIfLineNumberRecorder(0) {};
    std::vector<Token> tokenize(const char* fileName);

private:
    int prevIfLineNumberRecorder;
    bool isLegalLetter(char c);
    bool isLegalDigit(char c);
    bool isWhiteSpace(char c);
    bool isStatementTerminal(char c);
    bool isCurlyBracket(char c);
    bool isRoundBracket(char c);
    bool isConditionalChar(char c);
    bool isRelationalChar(char c);
    bool isAssignmentChar(char c);
    bool isRelationalExpression(std::string s);
    bool isLegalArithmeticChar(char c);
    std::vector<Token> handleKeyword(std::vector<Token> currentTokens, std::string candidateToken, std::string line,
                                     int charPos, int lineNumber);
    Token checkingAndGettingToken(char delimeter, TokenType type, std::string tokenId, std::string remainingLine,
                                             int lineNumber);
};
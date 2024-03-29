#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H
#endif//SPA_TOKENIZER_H
#pragma once
#include "Token.h"
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Tokenizer {
public:
    explicit Tokenizer() : prevIfLineNumberRecorder(0){};
    std::vector<Token> tokenize(const char *fileName);

private:
    int prevIfLineNumberRecorder;
    bool isLegalLetter(char c);
    bool isLegalDigit(char c);
    bool isWhiteSpace(char c);
    bool isStatementTerminal(char c);
    bool isCurlyBracket(char c);
    bool isRoundBracket(char c);
    bool isConditionalChar(char c);
    bool isConditionalExpression(std::string s);
    bool isRelationalChar(char c);
    bool isAssignmentChar(char c);
    bool isRelationalExpression(std::string s);
    bool isLegalArithmeticChar(char c);
    std::vector<Token> handleKeyword(std::vector<Token> currentTokens, std::string candidateToken, std::string line,
                                     int charPos, int lineNumber);
    Token checkingAndGettingToken(char delimeter, TokenType type, std::string tokenId, std::string remainingLine,
                                  int lineNumber);
    std::pair<int, std::vector<Token>> handleConditionalChar(std::vector<Token> currentTokens, std::string candidateToken,
                                                             std::string currLine, int currLineNum, int charPos);
    std::pair<int, std::vector<Token>> handleRelationalChar(std::vector<Token> currentTokens, std::string candidateToken,
                                                            std::string currLine, int currLineNum, int charPos);
    std::pair<int, std::vector<Token>> handleAssignmentChar(std::vector<Token> currentTokens, std::string candidateToken,
                                                            std::string currLine, int currLineNum, int charPos);
    std::pair<int, std::vector<Token>> handleLegalChar(std::vector<Token> currentTokens, std::string candidateToken,
                                                       std::string currLine, int currLineNum, int charPos);
    std::pair<int, std::vector<Token> > handleDigits(std::vector<Token> currentTokens, std::string candidateToken,
                                                    std::string currLine, int currLineNum, int charPos);
    std::pair<int, std::vector<Token> > handleCurlyBracket(std::vector<Token> currentTokens, std::string currLine,
                                                          int currLineNum, int charPos);
    std::pair<int, std::vector<Token> > handleRoundBracket(std::vector<Token> currentTokens, std::string currLine,
                                                          int currLineNum, int charPos);
};

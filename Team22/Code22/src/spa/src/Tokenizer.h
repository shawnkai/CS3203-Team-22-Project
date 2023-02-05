#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#endif //SPA_TOKENIZER_H
#pragma once
#include "Token.h"

class Tokenizer {
public:
    explicit Tokenizer();
    std::vector<Token> tokenize(const char* fileName);

private:
    bool isLegalLetter(char c);
    bool isWhiteSpace(char c);
    bool isStatementTerminal(char c);
    bool isCurlyBracket(char c);
    bool isRoundBracket(char c);
};
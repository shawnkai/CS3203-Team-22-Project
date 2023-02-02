#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#endif //SPA_TOKENIZER_H
#pragma once
#include "Token.h"

class Tokenizer {
public:
    explicit Tokenizer(const char* fileName);
    static std::vector<Token> tokenize(const char* fileName);
};
#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

#endif //SPA_TOKENIZER_H
#pragma once
#include "Token.h"

class Tokenizer {
public:
    explicit Tokenizer(const char* fileName);
    std::vector<Token> tokenize();
};
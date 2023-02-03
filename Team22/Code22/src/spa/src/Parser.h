#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "TNode.h"

using namespace std;

class Parser {
public:
    explicit Parser(std::vector<Token> tokenList) : tokenList(std::move(tokenList)), pos(0) {}
    unique_ptr<TNode> Parse();

private:
    vector<Token> tokenList;
    int pos;
    unique_ptr<TNode> parseProcedure();
    unique_ptr<TNode> parseStatement();
    unique_ptr<TNode> parseReadStatement();
};

int dummy();

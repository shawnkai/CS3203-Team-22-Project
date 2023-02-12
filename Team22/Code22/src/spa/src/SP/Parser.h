#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <utility>
#include "TNode.h"

using namespace std;

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokenList) : tokenList(tokenList), pos(0) {}
    TNode Parse();
private:
    vector<Token> tokenList;
    int pos;
    TNode parseProcedure();
    TNode parseStatement();
    TNode parseReadStatement();
    TNode parsePrintStatement();
    TNode parseAssignStatement();
    TNode parseWhileStatement();
    TNode parseIfStatement();
};


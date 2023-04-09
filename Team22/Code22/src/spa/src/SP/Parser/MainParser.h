#ifndef SPA_MAINPARSER_H
#define SPA_MAINPARSER_H

#include "TNode.h"
#include "memory"
#include <iostream>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

/**
 * MainParser is the parent or super class for all solid parsers in the Factory Method creation pattern.
 */
class MainParser {
public:
    MainParser(const std::vector<Token> &tokenList, std::shared_ptr<int> pos) : tokenList(tokenList), pos(std::move(pos)) {}

    virtual TNode parse() {
        std::cout << "Main Parser's parse should never be called" << std::endl;
        throw std::runtime_error("Should not call Main Parser's parse");
    }

protected:
    const std::vector<Token> &tokenList;
    std::shared_ptr<int> pos;
};

#endif//SPA_MAINPARSER_H

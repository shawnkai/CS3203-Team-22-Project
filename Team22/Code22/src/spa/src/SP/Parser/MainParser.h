#ifndef SPA_MAINPARSER_H
#define SPA_MAINPARSER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <sstream>
#include <utility>
#include <unordered_set>
#include "memory"
#include "TNode.h"

class MainParser {
public:
    MainParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) : tokenList(tokenList), pos(std::move(pos)) {}

    virtual TNode parse() {
        std::cout << "Main Parser's parse should never be called" << std::endl;
        throw std::runtime_error("Should not call Main Parser's parse");
    }

protected:
    const std::vector<Token>& tokenList;
    std::shared_ptr<int> pos;
};

#endif //SPA_MAINPARSER_H

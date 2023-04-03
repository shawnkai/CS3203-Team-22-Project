//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PARSERFACTORY_H
#define SPA_PARSERFACTORY_H

#include "MainParser.h"

class ParserFactory {
public:
    virtual shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) = 0;
};
#endif //SPA_PARSERFACTORY_H

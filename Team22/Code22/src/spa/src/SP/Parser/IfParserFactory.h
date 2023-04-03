//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_IFPARSERFACTORY_H
#define SPA_IFPARSERFACTORY_H

#include "ParserFactory.h"
#include "MainParser.h"
#include "IfParser.h"

class IfParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> ifPointer = std::make_shared<MainParser>(IfParser(tokenList, pos));
        return ifPointer;
    }
};
#endif //SPA_IFPARSERFACTORY_H

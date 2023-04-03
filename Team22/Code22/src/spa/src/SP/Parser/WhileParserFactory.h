//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_WHILEPARSERFACTORY_H
#define SPA_WHILEPARSERFACTORY_H
#include "WhileParser.h"
#include "ParserFactory.h"

class WhileParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> whilePointer = std::make_shared<MainParser>(WhileParser(tokenList, pos));
        return whilePointer;
    }
};
#endif //SPA_WHILEPARSERFACTORY_H

//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_READPARSERFACTORY_H
#define SPA_READPARSERFACTORY_H
#include "ParserFactory.h"
#include "ReadParser.h"

class ReadParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> readPointer = std::make_shared<MainParser>(ReadParser(tokenList, pos));
        return readPointer;
    }
};

#endif //SPA_READPARSERFACTORY_H

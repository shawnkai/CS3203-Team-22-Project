//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PRINTPARSERFACTORY_H
#define SPA_PRINTPARSERFACTORY_H

#include "PrintParser.h"
#include "ParserFactory.h"
class PrintParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> printPointer = std::make_shared<MainParser>(PrintParser(tokenList, pos));
        return printPointer;
    }
};

#endif //SPA_PRINTPARSERFACTORY_H

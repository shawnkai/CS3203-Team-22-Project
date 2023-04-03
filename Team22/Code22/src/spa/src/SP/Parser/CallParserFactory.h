//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_CALLPARSERFACTORY_H
#define SPA_CALLPARSERFACTORY_H

#include "CallParser.h"
#include "ParserFactory.h"

class CallParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> callPointer = std::make_shared<MainParser>(CallParser(tokenList, pos));
        return callPointer;
    }
};
#endif //SPA_CALLPARSERFACTORY_H

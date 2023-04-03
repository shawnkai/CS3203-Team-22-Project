//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_STATEMENTLISTPARSERFACTORY_H
#define SPA_STATEMENTLISTPARSERFACTORY_H

#include "ParserFactory.h"
#include "StatementListParser.h"

class StatementListParserFactory: public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> statementPointer = std::make_shared<MainParser>(StatementListParser(tokenList, pos));
        return statementPointer;
    }
};

#endif //SPA_STATEMENTLISTPARSERFACTORY_H

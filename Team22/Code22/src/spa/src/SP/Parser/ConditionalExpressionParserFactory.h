//
// Created by Yi Zhang on 4/4/23.
//

#ifndef SPA_CONDITIONALEXPRESSIONPARSERFACTORY_H
#define SPA_CONDITIONALEXPRESSIONPARSERFACTORY_H

#include "ParserFactory.h"
#include "ConditionalExpressionParser.h"

class ConditionalExpressionParserFactory: public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> conditionalExprPointer = std::make_shared<MainParser>(ConditionalExpressionParser(tokenList, pos));
        return conditionalExprPointer;
    }
};

#endif //SPA_CONDITIONALEXPRESSIONPARSERFACTORY_H

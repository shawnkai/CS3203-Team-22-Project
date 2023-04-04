//
// Created by Yi Zhang on 4/4/23.
//

#ifndef SPA_RELATIONALEXPRPARSERFACTORY_H
#define SPA_RELATIONALEXPRPARSERFACTORY_H

#include "ParserFactory.h"
#include "RelationalExprParser.h"

class RelationalExprParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> relationalExprPointer = std::make_shared<MainParser>(RelationalExprParser(tokenList, pos));
        return relationalExprPointer;
    }
};


#endif //SPA_RELATIONALEXPRPARSERFACTORY_H

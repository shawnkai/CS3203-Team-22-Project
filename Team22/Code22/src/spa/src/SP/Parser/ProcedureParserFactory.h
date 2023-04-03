//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PROCEDUREPARSERFACTORY_H
#define SPA_PROCEDUREPARSERFACTORY_H

#include "ParserFactory.h"
#include "ProcedureParser.h"
#include "MainParser.h"

class ProcedureParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> procedurePointer = std::make_shared<MainParser>(ProcedureParser(tokenList, pos));
        return procedurePointer;
    }
};

#endif //SPA_PROCEDUREPARSERFACTORY_H

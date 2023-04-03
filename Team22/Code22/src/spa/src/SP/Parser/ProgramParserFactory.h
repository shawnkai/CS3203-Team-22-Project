//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PROGRAMPARSERFACTORY_H
#define SPA_PROGRAMPARSERFACTORY_H
#include "ParserFactory.h"
#include "ProgramParser.h"
#include "MainParser.h"

class ProgramParserFactory : public ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> programmePointer = std::make_shared<MainParser>(ProgramParser(tokenList, pos));
        return programmePointer;
    }
};
#endif //SPA_PROGRAMPARSERFACTORY_H

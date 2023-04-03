
#ifndef SPA_ASSIGNPARSERFACTORY_H
#define SPA_ASSIGNPARSERFACTORY_H

#include "AssignParser.h"
#include "ParserFactory.h"

class AssignParserFactory: public ParserFactory {
public:
    shared_ptr<MainParser>  createParser(const std::vector<Token>& tokenList, std::shared_ptr<int> pos) override {
        std::shared_ptr<MainParser> assignPointer = std::make_shared<MainParser>(AssignParser(tokenList, pos));
        return assignPointer;
    }
};
#endif //SPA_ASSIGNPARSERFACTORY_H

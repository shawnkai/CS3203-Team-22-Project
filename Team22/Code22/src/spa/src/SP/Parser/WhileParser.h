
#ifndef SPA_WHILEPARSER_H
#define SPA_WHILEPARSER_H

#include "MainParser.h"
#include "ParserFactory.h"

class WhileParser : public MainParser {
public:
    using MainParser::MainParser;

    TNode parse() override;
};


#endif //SPA_WHILEPARSER_H

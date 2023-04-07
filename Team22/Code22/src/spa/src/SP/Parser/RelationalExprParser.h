//
// Created by Yi Zhang on 4/4/23.
//

#ifndef SPA_RELATIONALEXPRPARSER_H
#define SPA_RELATIONALEXPRPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class RelationalExprParser : public MainParser {
public:
    using MainParser::MainParser;

    TNode parse() override;
};


#endif//SPA_RELATIONALEXPRPARSER_H

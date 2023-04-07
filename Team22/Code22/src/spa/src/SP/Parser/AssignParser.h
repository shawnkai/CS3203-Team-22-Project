//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_ASSIGNPARSER_H
#define SPA_ASSIGNPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class AssignParser : public MainParser {
public:
    using MainParser::MainParser;
    TNode parse() override;
};


#endif//SPA_ASSIGNPARSER_H

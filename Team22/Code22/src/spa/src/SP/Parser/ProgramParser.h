//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PROGRAMPARSER_H
#define SPA_PROGRAMPARSER_H

#include "MainParser.h"
#include "ParserFactory.h"

class ProgramParser : public MainParser {
public:
    using MainParser::MainParser;

    TNode parse() override;
};

#endif //SPA_PROGRAMPARSER_H

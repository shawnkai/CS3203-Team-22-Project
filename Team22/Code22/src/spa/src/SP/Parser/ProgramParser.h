//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PROGRAMPARSER_H
#define SPA_PROGRAMPARSER_H

#include "MainParser.h"
#include "ProcedureParserFactory.h"

class ProgramParser : public MainParser {
public:
    using MainParser::MainParser;

    TreeNode parse() override;
};

#endif //SPA_PROGRAMPARSER_H

//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PRINTPARSER_H
#define SPA_PRINTPARSER_H

#include "MainParser.h"

class PrintParser : public MainParser{
public:
    using MainParser::MainParser;

    TNode parse() override;
};

#endif //SPA_PRINTPARSER_H

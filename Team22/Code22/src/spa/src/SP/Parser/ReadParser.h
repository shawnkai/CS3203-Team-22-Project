//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_READPARSER_H
#define SPA_READPARSER_H


#include "MainParser.h"

class ReadParser : public MainParser {
public:
    using MainParser::MainParser;

    TNode parse() override;
};


#endif//SPA_READPARSER_H

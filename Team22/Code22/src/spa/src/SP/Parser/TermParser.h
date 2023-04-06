//
// Created by Yi Zhang on 6/4/23.
//

#ifndef SPA_TERMPARSER_H
#define SPA_TERMPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class TermParser : public MainParser {
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_TERMPARSER_H

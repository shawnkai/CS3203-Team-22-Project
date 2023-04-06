//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_CALLPARSER_H
#define SPA_CALLPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class CallParser : public MainParser {
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_CALLPARSER_H

//
// Created by Yi Zhang on 6/4/23.
//

#ifndef SPA_FACTORPARSER_H
#define SPA_FACTORPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class FactorParser : public MainParser {
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_FACTORPARSER_H

//
// Created by Yi Zhang on 4/4/23.
//

#ifndef SPA_RELATIONALEXPRPARSER_H
#define SPA_RELATIONALEXPRPARSER_H


#include "MainParser.h"

class RelationalExprParser : public MainParser {
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;

};


#endif //SPA_RELATIONALEXPRPARSER_H

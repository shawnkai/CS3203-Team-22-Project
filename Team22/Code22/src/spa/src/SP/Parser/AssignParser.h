//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_ASSIGNPARSER_H
#define SPA_ASSIGNPARSER_H


#include "MainParser.h"

class AssignParser : public MainParser {
public:
    using MainParser::MainParser;
    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_ASSIGNPARSER_H

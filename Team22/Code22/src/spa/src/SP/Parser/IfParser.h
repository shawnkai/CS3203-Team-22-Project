//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_IFPARSER_H
#define SPA_IFPARSER_H

#include "MainParser.h"

class IfParser : public MainParser {
public:
    using MainParser::MainParser;

    TreeNode parse() override;
};

#endif //SPA_IFPARSER_H

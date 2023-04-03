
#ifndef SPA_WHILEPARSER_H
#define SPA_WHILEPARSER_H


#include "MainParser.h"

class WhileParser : public MainParser {
public:
    using MainParser::MainParser;

    TreeNode parse() override;
};


#endif //SPA_WHILEPARSER_H

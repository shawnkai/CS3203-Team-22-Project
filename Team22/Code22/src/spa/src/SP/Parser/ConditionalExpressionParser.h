//
// Created by Yi Zhang on 4/4/23.
//

#ifndef SPA_CONDITIONALEXPRESSIONPARSER_H
#define SPA_CONDITIONALEXPRESSIONPARSER_H

#include "MainParser.h"
#include "ConditionalExpressionParserFactory.h"

class ConditionalExpressionParser : public MainParser {
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_CONDITIONALEXPRESSIONPARSER_H

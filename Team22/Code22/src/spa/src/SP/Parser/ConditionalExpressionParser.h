//
// Created by Yi Zhang on 4/4/23.
//

#ifndef SPA_CONDITIONALEXPRESSIONPARSER_H
#define SPA_CONDITIONALEXPRESSIONPARSER_H

#include "MainParser.h"
#include "ParserFactory.h"

class ConditionalExpressionParser : public MainParser {
public:
    using MainParser::MainParser;

    TNode parse() override;
};


#endif //SPA_CONDITIONALEXPRESSIONPARSER_H

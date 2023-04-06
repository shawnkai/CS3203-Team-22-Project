
#ifndef SPA_EXPRESSIONPARSER_H
#define SPA_EXPRESSIONPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class ExpressionParser : public MainParser {
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;

};


#endif //SPA_EXPRESSIONPARSER_H

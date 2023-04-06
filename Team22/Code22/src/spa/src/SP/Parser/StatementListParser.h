//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_STATEMENTLISTPARSER_H
#define SPA_STATEMENTLISTPARSER_H

#include "StatementListNode.h"
#include "MainParser.h"
#include "ParserFactory.h"

class StatementListParser : public MainParser{
public:
    using MainParser::MainParser;

    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_STATEMENTLISTPARSER_H

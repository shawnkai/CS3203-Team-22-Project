//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PROCEDUREPARSER_H
#define SPA_PROCEDUREPARSER_H


#include "MainParser.h"
#include "ParserFactory.h"

class ProcedureParser : public MainParser{
public:
    using MainParser::MainParser;
    std::shared_ptr<TreeNode> parse() override;
};


#endif //SPA_PROCEDUREPARSER_H

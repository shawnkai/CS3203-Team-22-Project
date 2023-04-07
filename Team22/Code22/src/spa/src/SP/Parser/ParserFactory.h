//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PARSERFACTORY_H
#define SPA_PARSERFACTORY_H

#include "MainParser.h"
#include "ProgramParser.h"
#include "ProcedureParser.h"
#include "StatementListParser.h"
#include "IfParser.h"
#include "WhileParser.h"
#include "AssignParser.h"
#include "CallParser.h"
#include "PrintParser.h"
#include "ReadParser.h"
#include "ConditionalExpressionParser.h"
#include "RelationalExprParser.h"
#include "RelationalFactorParser.h"
#include "ExpressionParser.h"
#include "TermParser.h"
#include "FactorParser.h"

class ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(TokenType type, const std::vector<Token>& tokenList, std::shared_ptr<int> pos);
};
#endif //SPA_PARSERFACTORY_H

//
// Created by Yi Zhang on 3/4/23.
//

#ifndef SPA_PARSERFACTORY_H
#define SPA_PARSERFACTORY_H

#include "AssignParser.h"
#include "CallParser.h"
#include "ConditionalExpressionParser.h"
#include "ExpressionParser.h"
#include "FactorParser.h"
#include "IfParser.h"
#include "MainParser.h"
#include "PrintParser.h"
#include "ProcedureParser.h"
#include "ProgramParser.h"
#include "ReadParser.h"
#include "RelationalExprParser.h"
#include "RelationalFactorParser.h"
#include "StatementListParser.h"
#include "TermParser.h"
#include "WhileParser.h"

class ParserFactory {
public:
    std::shared_ptr<MainParser> createParser(TokenType type, const std::vector<Token> &tokenList, std::shared_ptr<int> pos);
};
#endif//SPA_PARSERFACTORY_H

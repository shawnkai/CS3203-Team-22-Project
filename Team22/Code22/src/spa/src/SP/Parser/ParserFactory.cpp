//
// Created by Yi Zhang on 6/4/23.
//
#include "ParserFactory.h"

std::shared_ptr<MainParser> ParserFactory::createParser(TokenType type, const std::vector<Token> &tokenList,
                                                        std::shared_ptr<int> pos) {
    switch (ToIntegral(type)) {
        case 1: return std::make_shared<ProgramParser>(ProgramParser(tokenList, pos));
        case 2: return std::make_shared<ProcedureParser>(ProcedureParser(tokenList, pos));
        case 3: return std::make_shared<StatementListParser>(StatementListParser(tokenList, pos));
        case 4: return std::make_shared<IfParser>(IfParser(tokenList, pos));
        case 5: return std::make_shared<WhileParser>(WhileParser(tokenList, pos));
        case 6: return std::make_shared<AssignParser>(AssignParser(tokenList, pos));
        case 7: return std::make_shared<CallParser>(CallParser(tokenList, pos));
        case 8: return std::make_shared<PrintParser>(PrintParser(tokenList, pos));
        case 9: return std::make_shared<ReadParser>(ReadParser(tokenList, pos));
        case 10: return std::make_shared<ConditionalExpressionParser>(ConditionalExpressionParser(tokenList, pos));
        case 11: return std::make_shared<RelationalExprParser>(RelationalExprParser(tokenList, pos));
        case 12: return std::make_shared<RelationalFactorParser>(RelationalFactorParser(tokenList, pos));
        case 13: return std::make_shared<ExpressionParser>(ExpressionParser(tokenList, pos));
        case 14: return std::make_shared<TermParser>(TermParser(tokenList, pos));
        case 15: return std::make_shared<FactorParser>(FactorParser(tokenList, pos));
        case 999: throw std::invalid_argument("Illegal token type: 999");
    }
}


#ifndef SPA_NEXTEXPRESSION_H
#define SPA_NEXTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

class NextExpression : public Expression {

public:
    explicit NextExpression(StmtRef* s1, StmtRef* s2);

    string toString() override;

    static tuple<StmtRef*, StmtRef*> generateStmtEntityPair(string arg1, string arg2, SynonymTable synonymTable);

    static vector<NextExpression*> extractNextExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsNextExpression(string query);

    ResultTable* evaluate(PKB pkb) override;
};

//class NextStarExpression : public Expression {
//public:
//    explicit NextStarExpression(StmtEntity* s1, StmtEntity* s2);
//
//    string toString() override;
//
//    static vector<NextStarExpression*> extractNextStarExpression(const string& query, const SynonymTable& synonymTable);
//
//    static bool containsNextStarExpression(string query);
//};

#endif //SPA_NEXTEXPRESSION_H
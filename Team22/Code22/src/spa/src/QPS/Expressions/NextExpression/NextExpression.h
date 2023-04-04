
#ifndef SPA_NEXTEXPRESSION_H
#define SPA_NEXTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

class NextExpression : public Expression {

public:
    explicit NextExpression(StmtRef* s1, StmtRef* s2);

    string toString() override;

    static vector<NextExpression*> extractNextExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsNextExpression(string query);

    ResultTable* evaluate(PKB pkb) override;
};

class NextStarExpression : public Expression {
public:
    explicit NextStarExpression(StmtRef* s1, StmtRef* s2);

    string toString() override;

    static vector<NextStarExpression*> extractNextStarExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsNextStarExpression(string query);

    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_NEXTEXPRESSION_H

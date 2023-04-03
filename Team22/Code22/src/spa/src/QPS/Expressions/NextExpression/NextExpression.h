
#ifndef SPA_NEXTEXPRESSION_H
#define SPA_NEXTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

class NextsExpression : public Expression {

private:
    string pkbAbstraction;

protected:
    static tuple<StmtEntity*, StmtEntity*> generateStmtEntityPair(string arg1, string arg2, SynonymTable synonymTable);

public:
    explicit NextsExpression(StmtEntity* s1, StmtEntity* s2, string pkbAbstraction);

    ResultTable evaluate(PKB pkb) override;

};

class NextExpression : public NextsExpression {
private:
    string pkbAbstraction;

public:
    explicit NextExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    static vector<NextExpression*> extractNextExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsNextExpression(string query);
};

class NextStarExpression : public NextsExpression {
public:
    explicit NextStarExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    static vector<NextStarExpression*> extractNextStarExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsNextStarExpression(string query);
};

#endif //SPA_NEXTEXPRESSION_H

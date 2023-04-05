
#ifndef SPA_NEXTEXPRESSION_H
#define SPA_NEXTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include <set>

class NextExpression : public Expression {

public:
    explicit NextExpression(StmtRef* s1, StmtRef* s2);

    string toString() override;

    static vector<NextExpression*> extractNextExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsNextExpression(string query);

    ResultTable* evaluate(PKB pkb) override;
};

class NextStarExpression : public Expression {
private:
    map<int, string> stmtTypes;

    void traversal(int current, map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                   map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, map<int, int> &seen, vector<string> prevs);

public:

    explicit NextStarExpression(StmtRef* s1, StmtRef* s2);

    string toString() override;

    static vector<NextStarExpression*> extractNextStarExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsNextStarExpression(string query);

    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_NEXTEXPRESSION_H

//
// Created by Tanishq Sharma on 5/4/23.
//

#ifndef SPA_AFFECTSEXPRESSION_H
#define SPA_AFFECTSEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include <set>

class AffectsExpression : public Expression {
private:
    unordered_map<int, vector<string>> ModifiedVars;
    unordered_map<int, vector<string>> UsedVars;
    vector<string> assignLines;

    void traversal(int current, map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                   unordered_map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen,
                   vector<string> prevs, unordered_map<int, vector<string>> validModifies);

public:
    explicit AffectsExpression(StmtRef* s1, StmtRef* s2);

    string toString() override;

    static vector<AffectsExpression*> extractAffectsExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsAffectsExpression(string query);

    ResultTable* evaluate(PKB pkb) override;
};

class AffectsStarExpression : public Expression {
private:
    void traversal(int current, map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                   unordered_map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen, vector<string> prevs);

public:

    explicit AffectsStarExpression(StmtRef* s1, StmtRef* s2);

    string toString() override;

    static vector<AffectsStarExpression*> extractAffectsStarExpression(const string& query, const SynonymTable& synonymTable);

    static bool containsAffectsStarExpression(string query);

    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_AFFECTSEXPRESSION_H

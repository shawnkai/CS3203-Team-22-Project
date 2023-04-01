//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_CALLSEXPRESSION_H
#define SPA_CALLSEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

using namespace std;

//Calls Expression Classes
class CallsExpression : public Expression {
public:
    explicit CallsExpression(NamedEntity* caller, NamedEntity* callee);

    static bool containsCallsExpression(string query);

    static vector<CallsExpression*> extractCallsExpression(const string& query, SynonymTable synonymTable);

    string toString() override;

    ResultTable* evaluate(PKB pkb) override;

    static NamedEntity* generateNamedEntity(string s, SynonymTable synonymTable);
};

class CallsStarExpression : public Expression {
public:
    explicit CallsStarExpression(NamedEntity* caller, NamedEntity* callee);

    static bool containsCallsStarExpression(string query);

    static vector<CallsStarExpression*> extractCallsStarExpression(const string& query, SynonymTable synonymTable);

    string toString() override;

    ResultTable* evaluate(PKB pkb) override;
};


#endif //SPA_CALLSEXPRESSION_H

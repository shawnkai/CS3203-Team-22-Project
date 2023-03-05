//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_USESEXPRESSION_H
#define SPA_USESEXPRESSION_H

#include <string>
#include <vector>
#include <regex>

#include "Utilities.h"
#include "QPS/Expressions/Expressions.h"
#include "QPS/Exceptions/Exceptions.h"
#include "QPS/Parser/SynonymTable.h"


class UsesExpression : public Expression {
public:
    explicit UsesExpression(DesignEntity* target);

    static bool containsUsesExpression(string query);

    static vector<UsesExpression*> extractUsesExpression(const string& query, SynonymTable synonymTable);
};

class UsesSExpression : public UsesExpression {

public:
    explicit UsesSExpression(StmtEntity* user, DesignEntity* target);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;
};

class UsesPExpression : public UsesExpression {
public:
    explicit UsesPExpression(NamedEntity* user, DesignEntity* target);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;
};


#endif //SPA_USESEXPRESSION_H

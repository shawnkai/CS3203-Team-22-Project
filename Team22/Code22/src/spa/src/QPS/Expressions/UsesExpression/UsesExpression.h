//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_USESEXPRESSION_H
#define SPA_USESEXPRESSION_H

#include <regex>
#include <string>
#include <vector>

#include "QPS/Exceptions/Exceptions.h"
#include "QPS/Expressions/Expressions.h"
#include "QPS/Parser/SynonymTable.h"
#include "Utilities.h"


class UsesExpression : public Expression {
private:
    static bool containsUsesExpression(string query);

public:
    explicit UsesExpression(DesignEntity *target);

    static vector<UsesExpression *> extractUsesExpression(const string &query, SynonymTable synonymTable);
};

class UsesSExpression : public UsesExpression {

public:
    explicit UsesSExpression(StmtRef *user, DesignEntity *target);

    string toString() override;

    ResultTable *evaluate(PKB pkb) override;
};

class UsesPExpression : public UsesExpression {
public:
    explicit UsesPExpression(NamedEntity *user, DesignEntity *target);

    string toString() override;

    ResultTable *evaluate(PKB pkb) override;
};


#endif//SPA_USESEXPRESSION_H

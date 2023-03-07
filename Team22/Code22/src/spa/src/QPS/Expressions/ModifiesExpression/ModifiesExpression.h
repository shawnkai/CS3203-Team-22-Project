//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_MODIFIESEXPRESSION_H
#define SPA_MODIFIESEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

using namespace std;

//Modifies Expression Classes
class ModifiesExpression : public Expression {
public:
    explicit ModifiesExpression(NamedEntity* target);

    static bool containsModifiesExpression(string query);

    static vector<ModifiesExpression*> extractModifiesExpression(const string& query, SynonymTable synonymTable);
};

class ModifiesSExpression : public ModifiesExpression {
public:
    explicit ModifiesSExpression(StmtEntity* modifier, NamedEntity* target);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;
};

class ModifiesPExpression : public ModifiesExpression {
public:
    explicit ModifiesPExpression(NamedEntity* modifier, NamedEntity* target);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;
};


#endif //SPA_MODIFIESEXPRESSION_H

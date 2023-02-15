//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#ifndef SPA_EXPRESSIONS_H
#define SPA_EXPRESSIONS_H

#include <string>
#include <utility>
#include <vector>
#include "QPS/Entities.h"
#include "PKB/PKB.h"
#include "Result.h"

using namespace std;

class Expression {
    protected:
        vector<DesignEntity*> entities;

    public:
        explicit Expression(vector<DesignEntity*> entities);

        virtual vector<string> evaluate(PKB pkb) = 0;

        virtual string toString() = 0;
};


class SelectExpression : public Expression {
private:
    vector<Expression*> conditions;

public:
    explicit SelectExpression(vector<DesignEntity*> entities, vector<Expression*> conditions);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;

};


//Modifies Expression Classes
class ModifiesExpression : public Expression {
public:
    ModifiesExpression(NamedEntity* target);
};

class ModifiesSExpression : public ModifiesExpression {
public:
    explicit ModifiesSExpression(StmtEntity* modifier, NamedEntity* target);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};

class ModifiesPExpression : public ModifiesExpression {
public:
    explicit ModifiesPExpression(NamedEntity* modifier, NamedEntity* target);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};


//Uses expression classes
class UsesExpression : public Expression {
public:
    explicit UsesExpression(DesignEntity* target);
};

class UsesSExpression : public UsesExpression {

public:
    explicit UsesSExpression(StmtEntity* user, DesignEntity* target);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};

class UsesPExpression : public UsesExpression {
public:
    explicit UsesPExpression(NamedEntity* user, DesignEntity* target);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};

class PatternExpression : public Expression {
private:
    string p1, p2;
public:
    explicit PatternExpression(DesignEntity *entity, string p1, string p2);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};




#endif //SPA_EXPRESSIONS_H

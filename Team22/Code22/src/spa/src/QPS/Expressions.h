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

        vector<DesignEntity*> getAllEntities();

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

class FollowsExpression: public Expression {
private:
    string pkbAbstraction;
public:
    explicit FollowsExpression(StmtEntity* s1, StmtEntity* s2);

    explicit FollowsExpression(StmtEntity* s1, StmtEntity* s2, string pkbAbstraction);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};

class FollowsStarExpression: public FollowsExpression {
public:
    explicit FollowsStarExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;
};

class ParentExpression: public Expression {
public:
    explicit ParentExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};

class ParentStarExpression: public Expression {
public:
    explicit ParentStarExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};

class PatternExpression : public Expression {
private:
    NamedEntity *p1;
    string p2;
public:
    explicit PatternExpression(DesignEntity *entity, NamedEntity *p1, string p2);

    string toString() override;

    vector<string> evaluate(PKB pkb) override;
};




#endif //SPA_EXPRESSIONS_H

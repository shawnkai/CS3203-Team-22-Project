//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#ifndef SPA_EXPRESSIONS_H
#define SPA_EXPRESSIONS_H

#include <string>
#include <utility>
#include <vector>
#include "QPS/Entities/Entities.h"
#include "PKB/PKB.h"
#include "Result.h"
#include "QPS/Evaluator/ResultTable.h"

using namespace std;

class Expression {
    /**
     * This is the parent class for all expressions and contains the virtual functions evaluate() and toString()
     * which overridden by its child classes
     */
    protected:
        vector<DesignEntity*> entities;

    public:
        explicit Expression(vector<DesignEntity*> entities);

        virtual ResultTable evaluate(PKB pkb) = 0;

        vector<DesignEntity*> getAllEntities();

        virtual string toString() = 0;
};


class SelectExpression : public Expression {
    /**
     * All Queries when parsed will return a SelectExpression type
     * which may consist of other Expressions called conditions
     */
private:
    vector<Expression*> conditions;

public:
    explicit SelectExpression(vector<DesignEntity*> entities, vector<Expression*> conditions);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;

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

    ResultTable evaluate(PKB pkb) override;
};

class ModifiesPExpression : public ModifiesExpression {
public:
    explicit ModifiesPExpression(NamedEntity* modifier, NamedEntity* target);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;
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

    ResultTable evaluate(PKB pkb) override;
};

class UsesPExpression : public UsesExpression {
public:
    explicit UsesPExpression(NamedEntity* user, DesignEntity* target);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;
};

class FAPSExpression: public Expression {
    /**
     * The FAPSExpression is the parent class for Follows, FollowsStar, Parent and ParentStar since their evaluations
     * are identical except for the PKB Abstraction each employs. To encapsulate this common evaluate we use the
     * FAPSExpression class
     */
private:
    string pkbAbstraction;

public:
    explicit FAPSExpression(StmtEntity* s1, StmtEntity* s2, string pkbAbstraction);

    ResultTable evaluate(PKB pkb) override;
};

class FollowsExpression: public FAPSExpression {
private:
    string pkbAbstraction;
public:
    explicit FollowsExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;
};

class FollowsStarExpression: public FAPSExpression {
public:
    explicit FollowsStarExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;
};

class ParentExpression: public FAPSExpression {
public:
    explicit ParentExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;
};

class ParentStarExpression: public FAPSExpression {
public:
    explicit ParentStarExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;
};

class PatternExpression : public Expression {
    /**
     * This class encapsulates a pattern expression which chooses a DesignEntity taking in the NamedEntity and
     * the string match for RHS (either exact or with wildcards)
     */
private:
    NamedEntity *p1;
    string p2;
public:
    explicit PatternExpression(DesignEntity *entity, NamedEntity *p1, string p2);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;
};




#endif //SPA_EXPRESSIONS_H

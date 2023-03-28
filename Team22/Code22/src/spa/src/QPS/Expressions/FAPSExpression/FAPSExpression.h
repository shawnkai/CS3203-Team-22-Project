//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_FAPSEXPRESSION_H
#define SPA_FAPSEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

class FAPSExpression: public Expression {
    /**
     * The FAPSExpression is the parent class for Follows, FollowsStar, Parent and ParentStar since their evaluations
     * are identical except for the PKB Abstraction each employs. To encapsulate this common evaluate we use the
     * FAPSExpression class
     */
private:
    string pkbAbstraction;

protected:
    static tuple<StmtEntity*, StmtEntity*> generateStmtEntityPair(string arg1, string arg2, SynonymTable synonymTable);

public:
    explicit FAPSExpression(StmtEntity* s1, StmtEntity* s2, string pkbAbstraction);

    ResultTable evaluate(PKB pkb) override;

};

class FollowsExpression: public FAPSExpression {
private:
    string pkbAbstraction;
    static bool containsFollowsExpression(string query);

public:
    explicit FollowsExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    static vector<FollowsExpression*> extractFollowsExpression(const string& query, const SynonymTable& synonymTable);
};

class FollowsStarExpression: public FAPSExpression {
private:
    static bool containsFollowsStarExpression(string query);

public:
    explicit FollowsStarExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    static vector<FollowsStarExpression*> extractFollowsStarExpression(const string& query, const SynonymTable& synonymTable);

};

class ParentExpression: public FAPSExpression {
private:
    static bool containsParentExpression(string query);

public:
    explicit ParentExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    static vector<ParentExpression*> extractParentExpression(const string& query, const SynonymTable& synonymTable);
};

class ParentStarExpression: public FAPSExpression {
private:
    static bool containsParentStarExpression(string query);

public:
    explicit ParentStarExpression(StmtEntity* s1, StmtEntity* s2);

    string toString() override;

    static vector<ParentStarExpression*> extractParentStarExpression(const string& query, const SynonymTable& synonymTable);
};


#endif //SPA_FAPSEXPRESSION_H

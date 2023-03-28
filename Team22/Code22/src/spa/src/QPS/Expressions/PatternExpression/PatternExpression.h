//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_PATTERNEXPRESSION_H
#define SPA_PATTERNEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include <string>

using namespace std;

class PatternExpression : public Expression {
protected:
    NamedEntity *p1;
    string p2;
    static bool containsPatternExpression(string query);

public:
    explicit PatternExpression(DesignEntity *entity, NamedEntity *p1);

    virtual string toString() {
        return "";
    };

    virtual ResultTable evaluate(PKB pkb) {
        return {{}};
    };

    static vector<PatternExpression*> extractPatternExpression(const string& query, SynonymTable synonymTable);
};

class AssignPatternExpression : public PatternExpression {
    /**
     * This class encapsulates a pattern expression which chooses a DesignEntity taking in the NamedEntity and
     * the string match for RHS (either exact or with wildcards)
     */
private:
     string p2;
public:
    explicit AssignPatternExpression(DesignEntity *entity, NamedEntity *p1, string p2);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;

};


class IfWhilePatternExpression : public PatternExpression {
public:

    IfWhilePatternExpression(DesignEntity *entity, NamedEntity *p1);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;

};

#endif //SPA_PATTERNEXPRESSION_H

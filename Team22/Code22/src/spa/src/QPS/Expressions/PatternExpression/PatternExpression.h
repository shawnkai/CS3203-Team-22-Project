//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_PATTERNEXPRESSION_H
#define SPA_PATTERNEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

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

    static bool containsPatternExpression(string query);

    static vector<PatternExpression*> extractPatternExpression(const string& query, SynonymTable synonymTable);
};

#endif //SPA_PATTERNEXPRESSION_H

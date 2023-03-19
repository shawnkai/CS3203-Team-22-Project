//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_SELECTEXPRESSION_H
#define SPA_SELECTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

class SelectExpression : public Expression {
    /**
     * All Queries when parsed will return a SelectExpression type
     * which may consist of other Expressions called conditions
     */
private:
    vector<Expression*> conditions;
    string synAttr;

public:
    explicit SelectExpression(DesignEntity* entity, vector<Expression*> conditions, string attribute = "");

    string toString() override;

    ResultTable evaluate(PKB pkb) override;

};

#endif //SPA_SELECTEXPRESSION_H

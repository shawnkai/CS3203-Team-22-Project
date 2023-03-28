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
    vector<string> synAttrs;

public:
    explicit SelectExpression(vector<DesignEntity*> entity, vector<string> attributes, vector<Expression*> conditions);

    string toString() override;

    ResultTable evaluate(PKB pkb) override;

};

#endif //SPA_SELECTEXPRESSION_H

//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_SELECTEXPRESSION_H
#define SPA_SELECTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include "QPS/Optimizer/Optimizer.h"
#include "QPS/Optimizer/parallel.h"

class SelectExpression : public Expression {
    /**
     * All Queries when parsed will return a SelectExpression type
     * which may consist of other Expressions called conditions
     */
private:
    vector<Expression*> conditions;
    vector<string> synAttrs;
    static regex SYNATTRREGEX;
    static pair<DesignEntity*, string> extractSynonymAndAttribute(const string& synAttr, SynonymTable synonymTable);

public:
    explicit SelectExpression(vector<DesignEntity*> entity, vector<string> attributes, vector<Expression*> conditions);
    static pair<vector<DesignEntity*>, vector<string>> extractSynonymsAndAttributes(const string& query, const SynonymTable& synonymTable);
    string toString() const override;
    static bool isBooleanType(const string& synAttr, SynonymTable synonymTable);
    vector<Expression*> getConditions();

    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_SELECTEXPRESSION_H

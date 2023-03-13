//
// Created by Tanishq Sharma on 10/3/23.
//

#ifndef SPA_ATTRCONDEXPRESSION_H
#define SPA_ATTRCONDEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include "QPS/Evaluator/ResultTable.h"
#include <string>

using namespace std;

class AttrCondExpression : public Expression {
private:
    string syn1attr;
    string syn2attr;

    static map<string, string> attrToType;
    static pair<DesignEntity*, pair<string, string>> generateSynAndAttrName(string ref, SynonymTable synonymTable);

public:
    AttrCondExpression(DesignEntity* syn1, string syn1attr, DesignEntity* syn2, string syn2attr);

    static bool containsAttrCondExpression(string query);

    string toString() override;

    static vector<AttrCondExpression*> extractAttrCondExpression(const string& query, const SynonymTable& synonymTable);

    ResultTable evaluate(PKB pkb) override;
};

#endif //SPA_ATTRCONDEXPRESSION_H
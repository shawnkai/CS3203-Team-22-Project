//
// Created by Atin Sakkeer Hussain on 06/02/2023.
//

#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include <string>
#include "Expressions.h"
#include "PKB/PKB.h"

using namespace std;

class QueryEvaluator {
private:
    PKB pkb;
public:
    QueryEvaluator(PKB pkb);

    vector<string> evaluate(Expression *expression);
};

#endif //SPA_EVALUATOR_H

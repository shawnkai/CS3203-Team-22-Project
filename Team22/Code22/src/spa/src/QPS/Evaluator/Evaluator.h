//
// Created by Atin Sakkeer Hussain on 06/02/2023.
//

#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include "PKB/PKB.h"
#include "QPS/Expressions/Expressions.h"
#include <string>

using namespace std;

class QueryEvaluator {
private:
    PKB pkb;

public:
    /**
     * Constructs a QueryEvaluator object.
     *
     * @param pkb The PKB object to be evaluated.
     */
    QueryEvaluator(PKB pkb);

    /**
     * Evaluates an Expression and returns the corresponding results.
     *
     * @param expression The Expression to be evaluated.
     *
     * @return A vector of string values that represents the results of the Expression evaluation.
     */
    vector<string> evaluate(Expression *expression);
};

#endif//SPA_EVALUATOR_H

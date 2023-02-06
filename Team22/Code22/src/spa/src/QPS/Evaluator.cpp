//
// Created by Atin Sakkeer Hussain on 06/02/2023.
//

#include "Evaluator.h"

QueryEvaluator::QueryEvaluator(PKB pkb) {
    this->pkb = pkb;
}

string QueryEvaluator::evaluate(Expression *expression) {
    return expression->evaluate(this->pkb).toString();
}
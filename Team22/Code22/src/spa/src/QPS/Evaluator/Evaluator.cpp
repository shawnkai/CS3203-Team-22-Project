//
// Created by Atin Sakkeer Hussain on 06/02/2023.
//

#include "Evaluator.h"

QueryEvaluator::QueryEvaluator(PKB pkb) {
    this->pkb = pkb;
}

vector<string> QueryEvaluator::evaluate(Expression *expression) {
    ResultTable* table = expression->evaluate(this->pkb);
    return table->getValues();
}
//
// Created by Atin Sakkeer Hussain on 08/04/2023.
//

#ifndef SPA_OPTIMIZER_H
#define SPA_OPTIMIZER_H

#include "QPS/Expressions/Expressions.h"

class QueryOptimizer {
public:
    static vector<vector<Expression*>> createGroups(const vector<Expression*>& conditions);
};


#endif //SPA_OPTIMIZER_H

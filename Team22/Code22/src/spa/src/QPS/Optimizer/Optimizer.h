//
// Created by Atin Sakkeer Hussain on 08/04/2023.
//

#ifndef SPA_OPTIMIZER_H
#define SPA_OPTIMIZER_H

#include "QPS/Expressions/Expressions.h"

/**
 * A Class for optimizing query evaluation by forming groups based on shared synonyms.
 */
class QueryOptimizer {
public:
    /**
     * Creates groups of sub-clauses that have shared synonyms.
     *
     * @param conditions A vector of Expression objects representing subclauses.
     *
     * @return A vector of vectors of Expression pointers, containing the grouped expressions.
     */
    static vector<vector<Expression*>> createGroups(const vector<Expression*>& conditions);
};


#endif //SPA_OPTIMIZER_H

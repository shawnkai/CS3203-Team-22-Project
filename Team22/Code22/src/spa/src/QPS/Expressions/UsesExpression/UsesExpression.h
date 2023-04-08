//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_USESEXPRESSION_H
#define SPA_USESEXPRESSION_H

#include <string>
#include <vector>
#include <regex>

#include "Utilities.h"
#include "QPS/Expressions/Expressions.h"
#include "QPS/Exceptions/Exceptions.h"
#include "QPS/QueryParser/SynonymTable.h"

/**
 * The UsesExpression class is responsible for evaluating and storing the Uses expression.
 *
 * It contains methods to check if a given query contains a Uses expression,
 * extract the Uses expressions from a given query, and evaluate the result of a Uses expression.
 */
class UsesExpression : public Expression {
private:
    /**
     * Checks if a given query contains the Uses expression.
     *
     * @param query The query to check.
     *
     * @return true if the query contains the Uses expression, false otherwise.
     */
    static bool containsUsesExpression(string query);

public:
    /**
     * Constructs a UsesExpression object with the given target.
     *
     * @param target The DesignEntity object representing the target of the Uses expression.
     */
    explicit UsesExpression(DesignEntity* target);

    /**
     * Extracts all the Uses expressions from a given query and stores them in a vector.
     *
     * @param query The query to extract Uses expressions from.
     * @param synonymTable A table containing synonyms for the query.
     *
     * @return A vector containing all the extracted Uses expressions.
     */
    static vector<UsesExpression*> extractUsesExpression(const string& query, SynonymTable synonymTable);
};

class UsesSExpression : public UsesExpression {

public:
    /**
    * Constructs a UsesSExpression object with the given user and target.
    *
    * @param user The StmtRef object representing the user of the Uses expression.
    * @param target The DesignEntity object representing the target of the Uses expression.
    */
    explicit UsesSExpression(StmtRef* user, DesignEntity* target);

    string toString() const override;

    /**
     * Evaluates the result of a UsesSExpression.
     *
     * @param pkb The PKB to evaluate the expression on.
     *
     * @return A ResultTable containing the result of the expression.
     */
    ResultTable* evaluate(PKB pkb) override;
};

class UsesPExpression : public UsesExpression {
public:
    /**
     * Constructs a UsesPExpression object with the given user and target.
     *
     * @param user The NamedEntity object representing the user of the Uses expression.
     * @param target The DesignEntity object representing the target of the Uses expression.
     */
    explicit UsesPExpression(NamedEntity* user, DesignEntity* target);

    string toString() const override;

    /**
     * Evaluates the result of a UsesPExpression.
     *
     * @param pkb The PKB to evaluate the expression on.
     *
     * @return A ResultTable containing the result of the expression.
     */
    ResultTable* evaluate(PKB pkb) override;
};


#endif //SPA_USESEXPRESSION_H

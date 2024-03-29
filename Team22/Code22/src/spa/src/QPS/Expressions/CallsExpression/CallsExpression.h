//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_CALLSEXPRESSION_H
#define SPA_CALLSEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

using namespace std;

/**
 * Class representing the Modifies design abstraction.
 */
class CallsExpression : public Expression {
public:
    /**
     * Constructs a new CallsExpression with the given caller and callee NamedEntities.
     *
     * @param caller The caller NamedEntity.
     * @param callee The callee NamedEntity.
     */
    explicit CallsExpression(NamedEntity* caller, NamedEntity* callee);

    /**
     * Returns true if the given query contains a CallsExpression, false otherwise.
     *
     * @param query The query to check.
     * @return True if the query contains a CallsExpression, false otherwise.
     */
    static bool containsCallsExpression(string query);

    /**
     * Extracts all CallsExpressions from the given query and synonymTable.
     *
     * @param query The query to extract CallsExpressions from.
     * @param synonymTable A map of synonyms to their corresponding NamedEntities and variables.
     *
     * @return A vector containing all extracted CallsExpressions.
     */
    static vector<CallsExpression*> extractCallsExpression(const string& query, SynonymTable synonymTable);

    string toString() const override;

    /**
     * Evaluates this CallsExpression using the given PKB.
     *
     * @param pkb The Program Knowledge Base used to evaluate the query.
     *
     * @return The ResultTable generated by the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;

    /**
     * Generates a NamedEntity with the given string and synonymTable.
     *
     * @param s The string to convert to a NamedEntity.
     * @param synonymTable A map of synonyms to their corresponding NamedEntities and variables.
     *
     * @return The NamedEntity corresponding to the given string.
     */
    static NamedEntity* generateNamedEntity(string s, SynonymTable synonymTable);
};

class CallsStarExpression : public Expression {
public:
    /**
     * Constructs a new CallsStarExpression with the given caller and callee NamedEntities.
     *
     * @param caller The caller NamedEntity.
     * @param callee The callee NamedEntity.
     */
    explicit CallsStarExpression(NamedEntity* caller, NamedEntity* callee);

    /**
     * Returns true if the given query contains a CallsStarExpression, false otherwise.
     *
     * @param query The query to check.
     *
     * @return True if the query contains a CallsStarExpression, false otherwise.
     */
    static bool containsCallsStarExpression(string query);

    /**
     * Extracts all CallsStarExpressions from the given query and synonymTable.
     *
     * @param query The query to extract CallsStarExpressions from.
     * @param synonymTable A map of synonyms to their corresponding NamedEntities and variables.
     *
     * @return A vector containing all extracted CallsStarExpressions.
     */
    static vector<CallsStarExpression*> extractCallsStarExpression(const string& query, SynonymTable synonymTable);

    string toString() const override;

    /**
     * Evaluates this CallsStarExpression using the given PKB.
     *
     * @param pkb The Program Knowledge Base used to evaluate the query.
     *
     * @return The ResultTable generated by the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;
};


#endif //SPA_CALLSEXPRESSION_H

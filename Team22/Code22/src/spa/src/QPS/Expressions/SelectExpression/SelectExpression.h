//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_SELECTEXPRESSION_H
#define SPA_SELECTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

/**
 * All Queries when parsed will return a SelectExpression type
 * which may consist of other Expressions called conditions
 */
class SelectExpression : public Expression {

private:
    vector<Expression*> conditions;
    vector<string> synAttrs;
    static regex SYNATTRREGEX;

    /**
     * Extracts the synonym and attribute from the given string.
     *
     * @param synAttr a string representing the synonym and attribute to extract
     * @param synonymTable a SynonymTable object representing the synonyms used in the query
     *
     * @return a pair, with the first element representing a DesignEntity pointer
     * and the second element representing a string representing the attribute for the entity
     */
    static pair<DesignEntity*, string> extractSynonymAndAttribute(const string& synAttr, SynonymTable synonymTable);

public:
    /**
     * Constructs a SelectExpression object.
     *
     * @param entities a vector of DesignEntity pointers representing the entities to be selected
     * @param attributes a vector of strings representing the attributes to be selected for each entity
     *
     * @param conditions a vector of Expression pointers representing the conditions to be checked
     */
    explicit SelectExpression(vector<DesignEntity*> entity, vector<string> attributes, vector<Expression*> conditions);

    /**
     * Extracts the synonyms and attributes from the given query.
     *
     * @param query the query string to extract synonyms and attributes from
     * @param synonymTable a SynonymTable object representing the synonyms used in the query
     *
     * @return a pair of vectors, with the first vector containing DesignEntity pointers and the second vector containing strings representing the attributes for each entity
     */
    static pair<vector<DesignEntity*>, vector<string>> extractSynonymsAndAttributes(const string& query, const SynonymTable& synonymTable);
    string toString() const override;

    /**
     * Returns true if the given synonym attribute is a BOOLEAN type.
     *
     * @param synAttr a string representing the synonym attribute to check
     * @param synonymTable a SynonymTable object representing the synonyms used in the query
     *
     * @return true if the given synonym attribute is a BOOLEAN type
     */
    static bool isBooleanType(const string& synAttr, SynonymTable synonymTable);

    /**
     * Evaluates this SelectExpression object and returns a ResultTable pointer representing the result of the query.
     *
     * @param pkb a PKB object to use in evaluating the query
     *
     * @return a ResultTable pointer representing the result of the query
     */
    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_SELECTEXPRESSION_H

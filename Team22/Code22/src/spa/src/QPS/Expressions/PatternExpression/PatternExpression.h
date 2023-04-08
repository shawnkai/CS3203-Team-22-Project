//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_PATTERNEXPRESSION_H
#define SPA_PATTERNEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include <string>

using namespace std;

/**
 * Class representing a pattern expression.
 */
class PatternExpression : public Expression {
protected:
    NamedEntity *p1;
    string p2;

    /**
     * Determines if a query string contains a pattern expression.
     *
     * @param query A string containing the query to search.
     *
     * @return True if the query contains a pattern expression, false otherwise.
     */
    static bool containsPatternExpression(string query);

public:
    /**
     * Constructor for the PatternExpression class.
     *
     * @param entity A pointer to a DesignEntity object.
     * @param p1 A pointer to a NamedEntity object.
     */
    explicit PatternExpression(DesignEntity *entity, NamedEntity *p1);

    virtual string toString() const {
        return "";
    };

    /**
     * Evaluates the pattern expression.
     *
     * @param pkb A PKB object.
     *
     * @return A ResultTable object containing the results of the evaluation.
     */
    virtual ResultTable* evaluate(PKB pkb) {
        return new BooleanFalseTable();
    };

    /**
     * Extracts pattern expressions from a query string.
     *
     * @param query A string containing the query to extract pattern expressions from.
     * @param synonymTable A SynonymTable object.
     *
     * @return A vector of pointers to PatternExpression objects.
     */
    static vector<PatternExpression*> extractPatternExpression(const string& query, SynonymTable synonymTable);
};

/**
 * Class representing an assign pattern expression.
 */
class AssignPatternExpression : public PatternExpression {

private:
     string p2;
public:
    /**
     * Constructor for the AssignPatternExpression class.
     *
     * @param entity A pointer to a DesignEntity object.
     * @param p1 A pointer to a NamedEntity object.
     *
     * @param p2 A string containing the second argument in the assign pattern expression.
     */
    explicit AssignPatternExpression(DesignEntity *entity, NamedEntity *p1, string p2);

    string toString() const override;

    /**
     * Evaluates an assign pattern expression.
     *
     * @param pkb A PKB object.
     *
     * @return A ResultTable object containing the results of the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;

};

/**
 * Class representing an if-while pattern expression.
 */
class IfWhilePatternExpression : public PatternExpression {
public:
    /**
     * Constructor for the IfWhilePatternExpression class.
     *
     * @param entity A pointer to a DesignEntity object.
     * @param p1 A pointer to a NamedEntity object.
     */
    IfWhilePatternExpression(DesignEntity *entity, NamedEntity *p1);

    string toString() const override;

    /**
     * Evaluates an if-while pattern expression.
     *
     * @param pkb A PKB object.
     *
     * @return A ResultTable object containing the results of the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_PATTERNEXPRESSION_H

//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_FAPSEXPRESSION_H
#define SPA_FAPSEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

/**
 * FAPSExpression is the parent class for Follows, Follows*, Parent, and Parent*. Its purpose is to encapsulate
 * the common evaluation of these four classes, which differs only in the PKB abstraction that they employ.
 */
class FAPSExpression: public Expression {

private:
    string pkbAbstraction;

protected:
    /**
     * Given two strings and a synonym table, generate a tuple consisting of two StmtRefs. This method is used to
     * generate the arguments for the constructors of FollowsExpression, FollowsStarExpression, ParentExpression, and
     * ParentStarExpression.
     *
     * @param arg1 The first argument to be converted to a StmtRef.
     * @param arg2 The second argument to be converted to a StmtRef.
     * @param synonymTable A map of synonyms to their corresponding StmtRefs and variables.
     * @return A tuple containing two StmtRefs representing the first and second arguments.
     */
    static tuple<StmtRef*, StmtRef*> generateStmtEntityPair(string arg1, string arg2, SynonymTable synonymTable);

public:
    /**
     * Construct a new FAPSExpression with the given StmtRefs and PKB abstraction.
     *
     * @param s1 The first StmtRef argument.
     * @param s2 The second StmtRef argument.
     * @param pkbAbstraction The PKB abstraction employed by this FAPSExpression.
     */
    explicit FAPSExpression(StmtRef* s1, StmtRef* s2, string pkbAbstraction);

    /**
     * Evaluate the query using the PKB and PKB abstraction of this FAPSExpression.
     *
     * @param pkb The Program Knowledge Base used to evaluate the query.
     * @return The ResultTable generated by the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;

};


/**
 * FollowsExpression evaluates queries that check if one statement follows another directly.
 */
class FollowsExpression: public FAPSExpression {
private:
    string pkbAbstraction;
    static bool containsFollowsExpression(string query);

public:
    /**
     * Construct a new FollowsExpression with the given StmtRefs.
     *
     * @param s1 The first StmtRef argument.
     * @param s2 The second StmtRef argument.
     */
    explicit FollowsExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extract all FollowsExpressions from the given query and SynonymTable.
     *
     * @param query The query to extract expressions from.
     * @param synonymTable The SynonymTable used to extract expressions.
     * @return A vector of FollowsExpressions extracted from the query.
     */
    static vector<FollowsExpression*> extractFollowsExpression(const string& query, const SynonymTable& synonymTable);
};

/**
 * FollowsStarExpression evaluates queries that check if one statement follows another, possibly indirectly.
 */
class FollowsStarExpression: public FAPSExpression {
private:
    static bool containsFollowsStarExpression(string query);

public:
    /**
     * Construct a new FollowsStarExpression with the given StmtRefs.
     *
     * @param s1 The first StmtRef argument.
     * @param s2 The second StmtRef argument.
     */
    explicit FollowsStarExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extracts all FollowsStarExpression objects from the given query and synonymTable.
     *
     * @param query the query string to extract FollowsStarExpression objects from.
     * @param synonymTable the SynonymTable to use for extraction.
     *
     * @return a vector of FollowsStarExpression objects extracted from the query and synonymTable.
     */
    static vector<FollowsStarExpression*> extractFollowsStarExpression(const string& query, const SynonymTable& synonymTable);

};

/**
 * The ParentExpression class represents the Parent relation.
 */
class ParentExpression: public FAPSExpression {
private:
    static bool containsParentExpression(string query);

public:
    /**
     * Creates a new ParentExpression object.
     *
     * @param s1 the first statement of the Parent relationship.
     * @param s2 the second statement of the Parent relationship.
     */
    explicit ParentExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extracts all ParentExpression objects from the given query and synonymTable.
     * @param query the query string to extract ParentExpression objects from.
     * @param synonymTable the SynonymTable to use for extraction.
     * @return a vector of ParentExpression objects extracted from the query and synonymTable.
     */
    static vector<ParentExpression*> extractParentExpression(const string& query, const SynonymTable& synonymTable);
};

/**
 * The ParentStarExpression class represents the Parent* design abstraction.
 */
class ParentStarExpression: public FAPSExpression {
private:
    /**
     * Returns true if the given query contains a ParentStarExpression, false otherwise.
     *
     * @param query The query to check for a ParentStarExpression.
     * @return True if the query contains a ParentStarExpression, false otherwise.
     */
    static bool containsParentStarExpression(string query);

public:
    /**
     * Constructs a new ParentStarExpression with the given StmtRefs.
     *
     * @param s1 The first StmtRef argument.
     * @param s2 The second StmtRef argument.
     */
    explicit ParentStarExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extracts all ParentStarExpressions from the given query and returns them in a vector.
     *
     * @param query The query to extract ParentStarExpressions from.
     * @param synonymTable A map of synonyms to their corresponding StmtRefs and variables.
     *
     * @return A vector containing all ParentStarExpressions extracted from the query.
     */
    static vector<ParentStarExpression*> extractParentStarExpression(const string& query, const SynonymTable& synonymTable);
};


#endif //SPA_FAPSEXPRESSION_H

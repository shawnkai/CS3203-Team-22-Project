//
// Created by Tanishq Sharma on 5/4/23.
//

#ifndef SPA_AFFECTSEXPRESSION_H
#define SPA_AFFECTSEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include <set>

/**
 * Class representing a Affects design abstraction.
 */
class AffectsExpression : public Expression {
private:
    unordered_map<int, vector<string>> ModifiedVars;
    unordered_map<int, vector<string>> UsedVars;
    vector<string> assignLines;

    /**
     * Traverses the CFG for Affects Expression and computes the results.
     *
     * @param current The current block in the control flow graph.
     * @param graph The control flow graph.
     * @param first A vector of the possible first arguments.
     * @param end A vector of the possible second arguments.
     * @param results A map that stores the results of the evaluation.
     * @param stmtsInBlock A map that stores the statements in each basic block.
     * @param seen A map that stores whether a block has been visited in the traversal.
     * @param prevs A vector of previous statements visited in the traversal.
     * @param validModifies A map of the each line to the valid variables modified.
     */
    void traversal(int current, map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                   unordered_map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen,
                   vector<string> prevs, unordered_map<int, vector<string>> validModifies);

public:
    /**
     * Constructs an Affects Expression object.
     *
     * @param s1 The left argument of the Affects Expression
     * @param s2 The right argument of the Affects Expression
     */
    explicit AffectsExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extracts all Affects Expression objects from a given query string.
     *
     * @param query The query string
     * @param synonymTable The SynonymTable containing all synonyms in the query
     *
     * @return A vector of Affects Expression objects extracted from the query string
     */
    static vector<AffectsExpression*> extractAffectsExpression(const string& query, const SynonymTable& synonymTable);

    /**
     * Determines whether a given query string contains an Affects Expression.
     *
     * @param query The query string
     *
     * @return true if the query string contains an Affects Expression, false otherwise
     */
    static bool containsAffectsExpression(string query);

    /**
     * Evaluates the Affects Expression and returns the corresponding result table.
     *
     * @param pkb The PKB to evaluate the expression on.
     *
     * @return The result table of the Affects Expression evaluation
     */
    ResultTable* evaluate(PKB pkb) override;
};

/**
 * Class representing a Affects* design abstraction.
 */
class AffectsStarExpression : public Expression {
private:
    unordered_map<int, vector<string>> ModifiedVars;
    unordered_map<int, vector<string>> UsedVars;
    vector<string> assignLines;

    /**
     * Traverses the CFG for Affects* Expression and computes the results.
     *
     * @param current The current block in the control flow graph.
     * @param graph The control flow graph.
     * @param first A vector of the possible first arguments.
     * @param end A vector of the possible second arguments.
     * @param results A map that stores the results of the evaluation.
     * @param stmtsInBlock A map that stores the statements in each basic block.
     * @param seen A map that stores whether a block has been visited in the traversal.
     * @param prevs A vector of previous statements visited in the traversal.
     * @param validModifies A map of the each line to the valid variables modified.
     */
    void traversal(int current, map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                   unordered_map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen,
                   vector<string> prevs, unordered_map<int, vector<string>> validModifies);

public:

    /**
     * Constructs an Affects Star Expression object.
     *
     * @param s1 The left argument of the Affects Star Expression
     * @param s2 The right argument of the Affects Star Expression
     */
    explicit AffectsStarExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extracts all Affects* Expression objects from a given query string.
     *
     * @param query The query string.
     * @param synonymTable The SynonymTable containing all synonyms in the query.
     *
     * @return A vector of Affects* Expression objects extracted from the query string.
     */
    static vector<AffectsStarExpression*> extractAffectsStarExpression(const string& query, const SynonymTable& synonymTable);

    /**
     * Determines whether a given query string contains an Affects Star Expression.
     *
     * @param query The query string.
     *
     * @return true if the query string contains an Affects Star Expression, false otherwise.
     */
    static bool containsAffectsStarExpression(string query);

    /**
     * Evaluates the Affects Star Expression and returns the corresponding result table.
     *
     * @param pkb The PKB to evaluate the expression on.
     *
     * @return The result table of the Affects Star Expression evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_AFFECTSEXPRESSION_H

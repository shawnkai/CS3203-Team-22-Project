
#ifndef SPA_NEXTEXPRESSION_H
#define SPA_NEXTEXPRESSION_H

#include "QPS/Expressions/Expressions.h"
#include <set>

/**
 * Class representing a Next design abstraction.
 */
class NextExpression : public Expression {

public:
    /**
     * Constructor for the NextExpression class.
     *
     * @param s1 A pointer to the first statement in the Next relationship.
     * @param s2 A pointer to the second statement in the Next relationship.
     */
    explicit NextExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extracts Next expressions from a query string.
     *
     * @param query A string containing the query to extract Next expressions from.
     * @param synonymTable A SynonymTable object.
     *
     * @return A vector of pointers to NextExpression objects.
     */
    static vector<NextExpression*> extractNextExpression(const string& query, const SynonymTable& synonymTable);

    /**
     * Determines if a query string contains a Next expression.
     *
     * @param query A string containing the query to search.
     *
     * @return True if the query contains a Next expression, false otherwise.
     */
    static bool containsNextExpression(string query);

    /**
     * Evaluates a Next expression.
     *
     * @param pkb A PKB object.
     *
     * @return A ResultTable object containing the results of the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;
};

/**
 * Class representing a Next* expression.
 */
class NextStarExpression : public Expression {
private:
    /**
     * Helper function that performs a depth-first search traversal on the control flow graph
     * and updates the results map with the statements that satisfy the Next* relationship
     * between the given source and target statements.
     *
     * @param current The current block in the control flow graph.
     * @param graph The control flow graph.
     * @param first A vector of the possible first arguments.
     * @param end A vector of the possible second arguments.
     * @param results A map that stores the results of the evaluation.
     * @param stmtsInBlock A map that stores the statements in each basic block.
     * @param seen A map that stores whether a block has been visited in the traversal.
     * @param prevs A vector of previous statements visited in the traversal.
     */
    void traversal(int current, unordered_map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                  unordered_map<int, set<int>> &results, unordered_map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen, vector<string> prevs);

public:
    /**
     * Constructor for the NextStarExpression class.
     *
     * @param s1 A pointer to the first statement in the Next* relationship.
     * @param s2 A pointer to the second statement in the Next* relationship.
     */
    explicit NextStarExpression(StmtRef* s1, StmtRef* s2);

    string toString() const override;

    /**
     * Extracts Next* expressions from a query string.
     *
     * @param query A string containing the query to extract Next* expressions from.
     * @param synonymTable A SynonymTable object.
     *
     * @return A vector of pointers to NextStarExpression objects.
     */
    static vector<NextStarExpression*> extractNextStarExpression(const string& query, const SynonymTable& synonymTable);

    /**
     * Determines if a query string contains a Next* expression.
     *
     * @param query A string containing the query to search.
     *
     * @return True if the query contains a Next* expression, false otherwise.
     */
    static bool containsNextStarExpression(string query);

    /**
     * Evaluates a Next* expression.
     *
     * @param pkb A PKB object.
     *
     * @return A ResultTable object containing the results of the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;

};

#endif //SPA_NEXTEXPRESSION_H

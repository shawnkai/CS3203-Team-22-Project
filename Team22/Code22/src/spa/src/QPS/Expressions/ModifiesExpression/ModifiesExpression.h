//
// Created by Tanishq Sharma on 5/3/23.
//

#ifndef SPA_MODIFIESEXPRESSION_H
#define SPA_MODIFIESEXPRESSION_H

#include "QPS/Expressions/Expressions.h"

using namespace std;

/**
 * Class representing the Modifies design abstraction.
 */
class ModifiesExpression : public Expression {
private:
    /**
     * Determines if a query string contains a Modifies expression.
     *
     * @param query A string containing the query to search.
     *
     * @return True if the query contains a Modifies expression, false otherwise.
     */
    static bool containsModifiesExpression(string query);

public:
    /**
     * Constructor for the ModifiesExpression class.
     *
     * @param target A pointer to a NamedEntity object representing the target entity.
     */
    explicit ModifiesExpression(NamedEntity* target);

    /**
     * Extracts Modifies expressions from a query string.
     *
     * @param query A string containing the query to extract Modifies expressions from.
     * @param synonymTable A SynonymTable object.
     *
     * @return A vector of pointers to ModifiesExpression objects.
     */
    static vector<ModifiesExpression*> extractModifiesExpression(const string& query, SynonymTable synonymTable);
};

/**
 * Class representing a Modifies statement expression.
 */
class ModifiesSExpression : public ModifiesExpression {
public:
    /**
     * Constructor for the ModifiesSExpression class.
     *
     * @param modifier A pointer to a StmtRef object representing the modifier statement.
     * @param target A pointer to a NamedEntity object representing the target entity.
     */
    explicit ModifiesSExpression(StmtRef* modifier, NamedEntity* target);

    string toString() const override;

    /**
     * Evaluates a Modifies statement expression.
     *
     * @param pkb A PKB object.
     *
     * @return A ResultTable object containing the results of the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;
};

/**
 * Class representing a Modifies procedure expression.
 */
class ModifiesPExpression : public ModifiesExpression {
public:
    /**
     * Constructor for the ModifiesPExpression class.
     *
     * @param modifier A pointer to a NamedEntity object representing the modifier procedure.
     * @param target A pointer to a NamedEntity object representing the target entity.
     */
    explicit ModifiesPExpression(NamedEntity* modifier, NamedEntity* target);

    string toString() const override;

    /**
     * Evaluates a Modifies procedure expression.
     *
     * @param pkb A PKB object.
     *
     * @return A ResultTable object containing the results of the evaluation.
     */
    ResultTable* evaluate(PKB pkb) override;
};


#endif //SPA_MODIFIESEXPRESSION_H

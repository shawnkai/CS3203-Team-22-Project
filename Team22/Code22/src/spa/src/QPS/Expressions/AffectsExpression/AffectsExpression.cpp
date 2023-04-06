//
// Created by Tanishq Sharma on 5/4/23.
//

#include "AffectsExpression.h"

AffectsExpression::AffectsExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string AffectsExpression::toString() {
    return "Affects(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

AffectsStarExpression::AffectsStarExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string AffectsStarExpression::toString() {
    return "Affects*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

vector<AffectsExpression*> AffectsExpression::extractAffectsExpression(const string& query, const SynonymTable& synonymTable) {
    if (!containsAffectsExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<AffectsExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, Expression::AFFECTSREGEX)) {
        pair<StmtRef*, StmtRef*> stmtEntityPair = Expression::generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);
        expressions.push_back(new AffectsExpression(stmtEntityPair.first, stmtEntityPair.second));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<AffectsStarExpression*> AffectsStarExpression::extractAffectsStarExpression(const string& query, const SynonymTable& synonymTable) {
    if (!containsAffectsStarExpression(query)) {
        return {};
    }

    smatch sm;
    string::const_iterator searchStart(query.begin());

    vector<AffectsStarExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, Expression::AFFECTSSTARREGEX)) {
        pair<StmtRef*, StmtRef*> stmtEntityPair = Expression::generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);
        expressions.push_back(new AffectsStarExpression(stmtEntityPair.first, stmtEntityPair.second));
        searchStart = sm.suffix().first;
    }
    return expressions;
}


bool AffectsExpression::containsAffectsExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), Expression::AFFECTSREGEX), std::sregex_iterator()) > 0;
}

bool AffectsStarExpression::containsAffectsStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), AFFECTSSTARREGEX), std::sregex_iterator()) > 0;
}

void AffectsExpression::traversal(int current, map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                                      unordered_map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen, vector<string> prevs) {
    //end of graph
    if (current == 0) {
        return;
    }

}

ResultTable* AffectsExpression::evaluate(PKB pkb) {
    return new BooleanFalseTable();
}

void AffectsStarExpression::traversal(int current, map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                                      unordered_map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen, vector<string> prevs) {
    //end of graph
    if (current == 0) {
        return;
    }

}

ResultTable *AffectsStarExpression::evaluate(PKB pkb) {
    return new BooleanFalseTable();
}
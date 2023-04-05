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
                                      unordered_map<int, set<int>> &results, map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> &seen,
                                      vector<string> prevs, unordered_map<int, vector<string>> validModifies) {
    //end of graph
    if (current == 0) {
        return;
    }

    //process any statements at most twice
    if (seen.find(current) != seen.end()) {
        if (seen.find(current)->second == 2) {
            return;
        } else {
            seen.find(current)->second += 1;
        }
    } else {
        seen.insert({current, 1});
    }

    for (int stmt : stmtsInBlock.find(current)->second) {
        for (string line : prevs) {
            vector<vector<string>> comb = {this->ModifiedVars.at(stmt), validModifies.at(stoi(line))};
            vector<string> common = Utilities::findIntersection(comb);
            for (string c : common) {
                std::remove(validModifies.at(stoi(line)).begin(), validModifies.at(stoi(line)).end(), c);
            }
        }

        if (Utilities::checkIfPresent(end, to_string(stmt))) {
            for (const auto& kv : results) {
                if (Utilities::checkIfPresent(prevs, to_string(kv.first))) {
                    vector<vector<string>> comb = {this->UsedVars.at(stmt), validModifies.at(kv.first)};
                    if (!Utilities::findIntersection(comb).empty()) {
                        results[kv.first].insert(stmt);
                    }
                }
            }
        }
        if (Utilities::checkIfPresent(first, to_string(stmt)) && results.find(stmt) == results.end()) {
            results.insert({stmt, {}});
        }
        prevs.push_back(to_string(stmt));
        validModifies.insert({stmt, this->ModifiedVars.at(stmt)});
    }

    for (int block : graph.find(current)->second) {
        traversal(block, graph, first, end, results, stmtsInBlock, seen, prevs, validModifies);
    }

}

ResultTable* AffectsExpression::evaluate(PKB pkb) {
    vector<Result> variableResults = pkb.getAllDesignEntity("VARIABLE");
    vector<Result> assignResults = pkb.getAllDesignEntity("ASSIGNMENT");
    for (Result res : assignResults) {
        for (const string& line : res.getQueryResult()) {
            this->assignLines.push_back(line);
            this->ModifiedVars.insert({stoi(line), {}});
            this->UsedVars.insert({stoi(line), {}});
        }
    }

    vector<Result> readResults = pkb.getAllDesignEntity("READ");
    for (Result res : readResults) {
        for (const string& line : res.getQueryResult()) {
            this->ModifiedVars.insert({stoi(line), {}});
        }
    }

    vector<Result> callResults = pkb.getAllDesignEntity("CALL");
    for (Result res : readResults) {
        for (const string& line : res.getQueryResult()) {
            this->ModifiedVars.insert({stoi(line), {}});
        }
    }

    for (Result res : variableResults) {
        Result modRes = pkb.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", res.getQueryEntityName()));
        Result useRes = pkb.getDesignAbstraction("USES", make_pair("ASSIGNMENT", res.getQueryEntityName()));
        for (const string& line : modRes.getQueryResult()) {
            if (line == "none") {
                continue;
            }
            this->ModifiedVars.at(stoi(line)).push_back(res.getQueryEntityName());
        }
        modRes = pkb.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", res.getQueryEntityName()));
        for (const string& line : modRes.getQueryResult()) {
            if (line == "none") {
                continue;
            }
            this->ModifiedVars.at(stoi(line)).push_back(res.getQueryEntityName());
        }
        modRes = pkb.getDesignAbstraction("MODIFIES", make_pair("READ", res.getQueryEntityName()));
        for (const string& line : modRes.getQueryResult()) {
            if (line == "none") {
                continue;
            }
            this->ModifiedVars.at(stoi(line)).push_back(res.getQueryEntityName());
        }
        for (const string& line : useRes.getQueryResult()) {
            if (line == "none") {
                continue;
            }
            this->UsedVars.at(stoi(line)).push_back(res.getQueryEntityName());
        }
    }

    for (const auto& kv : this->ModifiedVars) {
        ::printf("Modified in Line %d: ", kv.first);
        for(const string& line : kv.second) {
            ::printf("%s, ", line.c_str());
        }
        ::printf("\n");
    }

    for (const auto& kv : this->UsedVars) {
        ::printf("Used in Line %d: ", kv.first);
        for(const string& line : kv.second) {
            ::printf("%s, ", line.c_str());
        }
        ::printf("\n");
    }

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
//
// Created by Tanishq Sharma on 5/4/23.
//

#include "AffectsExpression.h"
#include <chrono>
using namespace std::chrono;

AffectsExpression::AffectsExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string AffectsExpression::toString() const {
    return "Affects(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

AffectsStarExpression::AffectsStarExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string AffectsStarExpression::toString() const {
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

        StmtRef* arg1 = stmtEntityPair.first;
        StmtRef* arg2 = stmtEntityPair.second;

        if (arg1->getType() != "STMTENTITY" && !(arg1->getType() == "ASSIGNMENT" || arg1->getType() == "STATEMENT")) {
            throw SemanticException();
        }
        if (arg2->getType() != "STMTENTITY" && !(arg2->getType() == "ASSIGNMENT" || arg2->getType() == "STATEMENT")) {
            throw SemanticException();
        }

        expressions.push_back(new AffectsExpression(arg1, arg2));
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

        StmtRef* arg1 = stmtEntityPair.first;
        StmtRef* arg2 = stmtEntityPair.second;

        if (arg1->getType() != "STMTENTITY" && !(arg1->getType() == "ASSIGNMENT" || arg1->getType() == "STATEMENT")) {
            throw SemanticException();
        }
        if (arg2->getType() != "STMTENTITY" && !(arg2->getType() == "ASSIGNMENT" || arg2->getType() == "STATEMENT")) {
            throw SemanticException();
        }

        expressions.push_back(new AffectsStarExpression(arg1, arg2));
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

void AffectsExpression::traversal(int current, unordered_map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                                      unordered_map<int, set<int>> &results, unordered_map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> seen,
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
        if (this->ModifiedVars.find(stmt) != this->ModifiedVars.end()) {
            if (Utilities::checkIfPresent(end, to_string(stmt))) {
                for (const auto& kv : results) {
                    if (this->UsedVars.find(stmt) != this->UsedVars.end() && Utilities::checkIfPresent(prevs, to_string(kv.first))) {
                        vector<vector<string>> comb = {this->UsedVars.at(stmt), validModifies.at(kv.first)};
                        if (!Utilities::findIntersection(comb).empty()) {
                            results[kv.first].insert(stmt);
                        }
                    }
                }
            }
            for (const string& line : prevs) {
                vector<vector<string>> comb = {this->ModifiedVars.at(stmt), validModifies.at(stoi(line))};
                vector<string> common = Utilities::findIntersection(comb);
                for (const string& c : common) {
                    validModifies.at(stoi(line)).erase(remove(validModifies.at(stoi(line)).begin(), validModifies.at(stoi(line)).end(), c), validModifies.at(stoi(line)).end());
                }
            }
            if (Utilities::checkIfPresent(first, to_string(stmt)) && results.find(stmt) == results.end()) {
                prevs.push_back(to_string(stmt));
                validModifies.insert({stmt, this->ModifiedVars.at(stmt)});
                results.insert({stmt, {}});
            }
        }
    }

    for (int block : graph.find(current)->second) {
        traversal(block, graph, first, end, results, stmtsInBlock, seen, prevs, validModifies);
    }

}

ResultTable* AffectsExpression::evaluate(PKB pkb) {

    unordered_map<string, unordered_set<string>> assignResults = pkb.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "ASSIGNMENT");
    for (const auto& kv : assignResults) {
        int line = stoi(kv.first);
        if (this->ModifiedVars.find(line) == this->ModifiedVars.end()) {
            this->ModifiedVars.insert({line, {}});
            this->assignLines.push_back(kv.first);
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->ModifiedVars.at(line).push_back(variable);
            }
        }
    }

    unordered_map<string, unordered_set<string>> readResults = pkb.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "READ");
    for (const auto& kv : readResults) {
        int line = stoi(kv.first);
        if (this->ModifiedVars.find(line) == this->ModifiedVars.end()) {
            this->ModifiedVars.insert({line, {}});
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->ModifiedVars.at(line).push_back(variable);
            }
        }
    }

    unordered_map<string, unordered_set<string>> callResults = pkb.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "PROCEDURECALL");
    for (const auto& kv : callResults) {
        int line = stoi(kv.first);
        if (this->ModifiedVars.find(line) == this->ModifiedVars.end()) {
            this->ModifiedVars.insert({line, {}});
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->ModifiedVars.at(line).push_back(variable);
            }
        }
    }

    unordered_map<string, unordered_set<string>> usesResults = pkb.getAllVariablesCapturedByDesignAbstraction("USES", "ASSIGNMENT");
    for (const auto& kv : usesResults) {
        int line = stoi(kv.first);
        if (this->UsedVars.find(line) == this->UsedVars.end()) {
            this->UsedVars.insert({line, {}});
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->UsedVars.at(line).push_back(variable);
            }
        }
    }

    vector<string> firstLine;
    vector<string> secondLine;

    if (dynamic_cast<StmtEntity*>(this->entities[0])) {
        firstLine.push_back(to_string(dynamic_cast<StmtEntity*>(this->entities[0])->getLine()));
    } else {
        auto vars1 = pkb.getAllDesignEntity("ASSIGNMENT");
        for (Result res : vars1) {
            for (const string& line : res.getQueryResult()) {
                if (Utilities::checkIfPresent(this->assignLines, line)) {
                    firstLine.push_back(line);
                }
            }
        }
    }

    set<string> s1(firstLine.begin(), firstLine.end());
    firstLine.assign( s1.begin(), s1.end());

    if (dynamic_cast<StmtEntity*>(this->entities[1])) {
        secondLine.push_back(to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()));
    } else {
        auto vars2 = pkb.getAllDesignEntity("ASSIGNMENT");
        for (Result res : vars2) {
            for (const string& line : res.getQueryResult()) {
                if (Utilities::checkIfPresent(this->assignLines, line)) {
                    secondLine.push_back(line);
                }
            }
        }
    }

    set<string> s2(secondLine.begin(), secondLine.end());
    secondLine.assign( s2.begin(), s2.end());

    vector<Result> procResults = pkb.getAllDesignEntity("PROCEDURE");
    vector<string> procs;
    for (auto res : procResults) {
        procs.push_back(res.getQueryEntityName());
    }

    unordered_map<string, vector<string>> finalResult = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
    bool found = false;
    for (const string& proc : procs) {
        auto startTime = high_resolution_clock::now();
        auto graph = pkb.getBlockToBlockDatabase(proc);
        auto blockStatements = pkb.getBlockToStatementNumbersDatabase(proc);
        if (graph.empty()) {
            continue;
        }
        vector<int> blocks;
        for (const auto& kv : graph) {
            blocks.push_back(kv.first);
            vector<int> stmts = blockStatements.at(kv.first);
        }
        int start = *min_element(blocks.begin(), blocks.end());
        unordered_map<int, set<int>> results = {};
        unordered_map<int, int> seen;
        traversal(start, graph, firstLine, secondLine, results, blockStatements, seen, {}, {});
        for (const auto& kv : results) {
            for (int v : kv.second) {
                finalResult.at(this->entities[0]->toString()).push_back(to_string(kv.first));
                finalResult.at(this->entities[1]->toString()).push_back(to_string(v));
            }
        }
        auto stopTime = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stopTime - startTime);
        ::printf("Traversal Time: %f ms\n", duration.count() * 0.001);
    }

    if (!dynamic_cast<SynonymStmtEntity*>(this->entities[0]) && !dynamic_cast<SynonymStmtEntity*>(this->entities[1])) {
        if ((new ResultTable(finalResult))->getSize() != 0) {
            return new BooleanTrueTable();
        }
        else {
            return new BooleanFalseTable();
        }
    }
    else if (!dynamic_cast<SynonymStmtEntity*>(this->entities[0])) {
        return (new ResultTable(finalResult))->getColumns({this->entities[1]->toString()});
    }
    else if (!dynamic_cast<SynonymStmtEntity*>(this->entities[1])) {
        return (new ResultTable(finalResult))->getColumns({this->entities[0]->toString()});
    }
    return new ResultTable(finalResult);

}

void AffectsStarExpression::traversal(int current, unordered_map<int, vector<int>> &graph, vector<string> &first, vector<string> &end,
                                      unordered_map<int, set<int>> &results, unordered_map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> seen,
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
        if (this->ModifiedVars.find(stmt) != this->ModifiedVars.end()) {
            unordered_set<int> used;
            if (Utilities::checkIfPresent(end, to_string(stmt))) {
                for (const auto& kv : results) {
                    if (this->UsedVars.find(stmt) != this->UsedVars.end() && Utilities::checkIfPresent(prevs, to_string(kv.first))) {
                        vector<vector<string>> comb = {this->UsedVars.at(stmt), validModifies.at(kv.first)};
                        if (!Utilities::findIntersection(comb).empty()) {
                            results[kv.first].insert(stmt);
                            used.insert(kv.first);
                        }
                    }
                }
            }
            for (const string& line : prevs) {
                if (!validModifies.at(stoi(line)).empty()) {
                    vector<vector<string>> comb = {this->ModifiedVars.at(stmt), validModifies.at(stoi(line))};
                    vector<string> common = Utilities::findIntersection(comb);
                    for (const string& c : common) {
                        validModifies.at(stoi(line)).erase(remove(validModifies.at(stoi(line)).begin(), validModifies.at(stoi(line)).end(), c), validModifies.at(stoi(line)).end());
                    }
                    if (used.find(stoi(line)) != used.end()) {
                        Utilities::concatenateVectors(validModifies.at(stoi(line)), this->ModifiedVars.at(stmt));
                    }
                }
            }
            if (Utilities::checkIfPresent(first, to_string(stmt)) && results.find(stmt) == results.end()) {
                prevs.push_back(to_string(stmt));
                validModifies.insert({stmt, this->ModifiedVars.at(stmt)});
                results.insert({stmt, {}});
            }
        }
    }

    for (int block : graph.find(current)->second) {
        traversal(block, graph, first, end, results, stmtsInBlock, seen, prevs, validModifies);
    }
}

ResultTable *AffectsStarExpression::evaluate(PKB pkb) {
    unordered_map<string, unordered_set<string>> assignResults = pkb.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "ASSIGNMENT");
    for (const auto& kv : assignResults) {
        int line = stoi(kv.first);
        if (this->ModifiedVars.find(line) == this->ModifiedVars.end()) {
            this->ModifiedVars.insert({line, {}});
            this->assignLines.push_back(kv.first);
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->ModifiedVars.at(line).push_back(variable);
            }
        }
    }

    unordered_map<string, unordered_set<string>> readResults = pkb.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "READ");
    for (const auto& kv : readResults) {
        int line = stoi(kv.first);
        if (this->ModifiedVars.find(line) == this->ModifiedVars.end()) {
            this->ModifiedVars.insert({line, {}});
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->ModifiedVars.at(line).push_back(variable);
            }
        }
    }

    unordered_map<string, unordered_set<string>> callResults = pkb.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "PROCEDURECALL");
    for (const auto& kv : callResults) {
        int line = stoi(kv.first);
        if (this->ModifiedVars.find(line) == this->ModifiedVars.end()) {
            this->ModifiedVars.insert({line, {}});
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->ModifiedVars.at(line).push_back(variable);
            }
        }
    }

    unordered_map<string, unordered_set<string>> usesResults = pkb.getAllVariablesCapturedByDesignAbstraction("USES", "ASSIGNMENT");
    for (const auto& kv : usesResults) {
        int line = stoi(kv.first);
        if (this->UsedVars.find(line) == this->UsedVars.end()) {
            this->UsedVars.insert({line, {}});
        }
        for (const string& variable : kv.second) {
            if (Utilities::isValidVariableName(variable)) {
                this->UsedVars.at(line).push_back(variable);
            }
        }
    }

    vector<string> firstLine;
    vector<string> secondLine;

    if (dynamic_cast<StmtEntity*>(this->entities[0])) {
        firstLine.push_back(to_string(dynamic_cast<StmtEntity*>(this->entities[0])->getLine()));
    } else {
        auto vars1 = pkb.getAllDesignEntity("ASSIGNMENT");
        for (Result res : vars1) {
            for (const string& line : res.getQueryResult()) {
                if (Utilities::checkIfPresent(this->assignLines, line)) {
                    firstLine.push_back(line);
                }
            }
        }
    }

    set<string> s1(firstLine.begin(), firstLine.end());
    firstLine.assign( s1.begin(), s1.end());

    if (dynamic_cast<StmtEntity*>(this->entities[1])) {
        secondLine.push_back(to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()));
    } else {
        auto vars2 = pkb.getAllDesignEntity("ASSIGNMENT");
        for (Result res : vars2) {
            for (const string& line : res.getQueryResult()) {
                if (Utilities::checkIfPresent(this->assignLines, line)) {
                    secondLine.push_back(line);
                }
            }
        }
    }

    set<string> s2(secondLine.begin(), secondLine.end());
    secondLine.assign( s2.begin(), s2.end());

    vector<Result> procResults = pkb.getAllDesignEntity("PROCEDURE");
    vector<string> procs;
    for (auto res : procResults) {
        procs.push_back(res.getQueryEntityName());
    }

    unordered_map<string, vector<string>> finalResult = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};

    for (const string& proc : procs) {
        auto startTime = high_resolution_clock::now();
        auto graph = pkb.getBlockToBlockDatabase(proc);
        auto blockStatements = pkb.getBlockToStatementNumbersDatabase(proc);
        if (graph.empty()) {
            continue;
        }
        vector<int> blocks;
        for (const auto& kv : graph) {
            blocks.push_back(kv.first);
            vector<int> stmts = blockStatements.at(kv.first);
        }
        int start = *min_element(blocks.begin(), blocks.end());
        unordered_map<int, set<int>> results = {};
        unordered_map<int, int> seen;
        traversal(start, graph, firstLine, secondLine, results, blockStatements, seen, {}, {});
        for (const auto& kv : results) {
            for (int v : kv.second) {
                finalResult.at(this->entities[0]->toString()).push_back(to_string(kv.first));
                finalResult.at(this->entities[1]->toString()).push_back(to_string(v));
            }
        }
        auto stopTime = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stopTime - startTime);
        ::printf("Traversal Time: %f ms\n", duration.count() * 0.001);
    }

    if (!dynamic_cast<SynonymStmtEntity*>(this->entities[0]) && !dynamic_cast<SynonymStmtEntity*>(this->entities[1])) {
        if ((new ResultTable(finalResult))->getSize() != 0) {
            return new BooleanTrueTable();
        }
        else {
            return new BooleanFalseTable();
        }
    }
    else if (!dynamic_cast<SynonymStmtEntity*>(this->entities[0])) {
        return (new ResultTable(finalResult))->getColumns({this->entities[1]->toString()});
    }
    else if (!dynamic_cast<SynonymStmtEntity*>(this->entities[1])) {
        return (new ResultTable(finalResult))->getColumns({this->entities[0]->toString()});
    }
    return new ResultTable(finalResult);
}
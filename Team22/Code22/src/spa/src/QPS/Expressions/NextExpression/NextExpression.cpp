#include "NextExpression.h"

#include <chrono>
using namespace std::chrono;

ResultTable* NextExpression::evaluate(PKB pkb) {
    vector<string> firstLine;
    vector<string> secondLine;

    if (dynamic_cast<StmtEntity*>(this->entities[0])) {
        firstLine.push_back(to_string(dynamic_cast<StmtEntity*>(this->entities[0])->getLine()));
    } else {
        auto vars1 = pkb.getAllDesignEntity(this->entities[0]->getType());
        for (Result res : vars1) {
            for (const string& line : res.getQueryResult()) {
                firstLine.push_back(line);
            }
        }
    }

    if (dynamic_cast<StmtEntity*>(this->entities[1])) {
        secondLine.push_back(to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()));
    } else {
        auto vars2 = pkb.getAllDesignEntity(this->entities[1]->getType());
        for (Result res : vars2) {
            for (const string& line : res.getQueryResult()) {
                secondLine.push_back(line);
            }
        }
    }

   unordered_map<string, vector<string>> results = { {this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}} };
    vector<pair<string, string>> seen;
    for (const string& line : firstLine) {
        Result next = pkb.getDesignAbstraction("NEXT", make_tuple("_", line));
        vector<vector<string>> all_vectors;
        all_vectors.push_back(secondLine);
        all_vectors.push_back(next.getQueryResult());
        vector<string> followsSatisfied = Utilities::findIntersection(all_vectors);
        for (const string& r : followsSatisfied) {
            if (find(seen.begin(), seen.end(), make_pair(line, r)) == seen.cend()) {
                results.find(this->entities[0]->toString())->second.push_back(line);
                results.find(this->entities[1]->toString())->second.push_back(r);
                seen.emplace_back(line, r);
            }
        }
    }

    if (!dynamic_cast<SynonymStmtEntity*>(this->entities[0]) && !dynamic_cast<SynonymStmtEntity*>(this->entities[1])) {
        if ((new ResultTable(results))->getSize() != 0) {
            return new BooleanTrueTable();
        }
        else {
            return new BooleanFalseTable();
        }
    }
    else if (!dynamic_cast<SynonymStmtEntity*>(this->entities[0])) {
        return (new ResultTable(results))->getColumns({this->entities[1]->toString()});
    }
    else if (!dynamic_cast<SynonymStmtEntity*>(this->entities[1])) {
        return (new ResultTable(results))->getColumns({this->entities[0]->toString()});
    }
    return new ResultTable(results);

}

void NextStarExpression::traversal(int current, unordered_map<int, vector<int>> &graph, unordered_set<string> &first, unordered_set<string> &end,
                             unordered_map<int, set<int>> &results, unordered_map<int, vector<int>> &stmtsInBlock, unordered_map<int, int> seen, unordered_set<string> prevs) {
    //end of graph
    if (current == 0) {
        return;
    }

    //process any statements at most twice
    if (seen.find(current) != seen.end()) {
        if (seen.find(current)->second == 2) {
            seen.erase(current);
            return;
        } else {
            seen.find(current)->second += 1;
        }
    } else {
        seen.insert({current, 1});
    }

    for (int stmt : stmtsInBlock.find(current)->second) {
        if (end.find(to_string(stmt)) != end.end()) {
            for (const auto& kv : results) {
                if (prevs.find(to_string(kv.first)) != prevs.end()) {
                    results[kv.first].insert(stmt);
                }
            }
        }
        if (first.find(to_string(stmt)) != first.end() && results.find(stmt) == results.end()) {
            results.insert({stmt, {}});
        }
        prevs.insert(to_string(stmt));
    }

    for (int block : graph.find(current)->second) {
        traversal(block, graph, first, end, results, stmtsInBlock, seen, prevs);
    }
}

ResultTable* NextStarExpression::evaluate(PKB pkb) {
    unordered_set<string> firstLine;
    unordered_set<string> secondLine;

    if (dynamic_cast<StmtEntity*>(this->entities[0])) {
        firstLine.insert(to_string(dynamic_cast<StmtEntity*>(this->entities[0])->getLine()));
    } else {
        auto vars1 = pkb.getAllDesignEntity(this->entities[0]->getType());
        for (Result res : vars1) {
            for (const string& line : res.getQueryResult()) {
                firstLine.insert(line);
            }
        }
    }

    if (dynamic_cast<StmtEntity*>(this->entities[1])) {
        secondLine.insert(to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()));
    } else {
        auto vars2 = pkb.getAllDesignEntity(this->entities[1]->getType());
        for (Result res : vars2) {
            for (const string& line : res.getQueryResult()) {
                secondLine.insert(line);
            }
        }
    }

    unordered_set<string> s2(secondLine.begin(), secondLine.end());

    vector<Result> procResults = pkb.getAllDesignEntity("PROCEDURE");
    vector<string> procs;
    procs.reserve(procResults.size());
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
        traversal(start, graph, firstLine, secondLine, results, blockStatements, seen, {});
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

NextExpression::NextExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string NextExpression::toString() const {
    return "Next(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

NextStarExpression::NextStarExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string NextStarExpression::toString() const {
    return "Next*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

vector<NextExpression*> NextExpression::extractNextExpression(const string& query, const SynonymTable& synonymTable) {
    if (!containsNextExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<NextExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, Expression::NEXTREGEX)) {
        pair<StmtRef*, StmtRef*> stmtEntityPair = Expression::generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);
        expressions.push_back(new NextExpression(stmtEntityPair.first, stmtEntityPair.second));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<NextStarExpression*> NextStarExpression::extractNextStarExpression(const string& query, const SynonymTable& synonymTable) {
    if (!containsNextStarExpression(query)) {
        return {};
    }

    smatch sm;
    string::const_iterator searchStart(query.begin());

    vector<NextStarExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, Expression::NEXTSTARREGEX)) {
        pair<StmtRef*, StmtRef*> stmtEntityPair = Expression::generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);
        expressions.push_back(new NextStarExpression(stmtEntityPair.first, stmtEntityPair.second));
        searchStart = sm.suffix().first;
    }
    return expressions;
}


bool NextExpression::containsNextExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), Expression::NEXTREGEX), std::sregex_iterator()) > 0;
}

bool NextStarExpression::containsNextStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), NEXTSTARREGEX), std::sregex_iterator()) > 0;
}





#include "NEXTExpression.h"

NextsExpression::NextsExpression(StmtEntity* s1, StmtEntity* s2, string pkbAbstraction) : Expression({ s1, s2 }) {
    this->pkbAbstraction = pkbAbstraction;
}

ResultTable NextsExpression::evaluate(PKB pkb) {
    if (this->entities[0]->toString() == "_" && this->entities[1]->toString() == "_") {
        return ResultTable({ {"_", {"-"}} });
    }
    else if (this->entities[0]->toString() == this->entities[1]->toString()) {
        return ResultTable({ {this->entities[0]->toString(), {}} });
    }
    else if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() == -1 && dynamic_cast<StmtEntity*>(this->entities[1])->getLine() == -1) {
        auto vars1 = pkb.getAllDesignEntity(this->entities[0]->getType());
        auto vars2 = pkb.getAllDesignEntity(this->entities[1]->getType());
        vector<string> possibleLines;
        for (Result res : vars2) {
            for (string l : res.getQueryResult()) {
                possibleLines.push_back(l);
            }
        }
        vector<string> followedLines;
        map<string, vector<string>> results = { {this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}} };
        vector<pair<string, string>> seen;
        for (Result res : vars1) {
            for (const string& line : res.getQueryResult()) {
                Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", line));
                vector<vector<string>> all_vectors;
                all_vectors.push_back(possibleLines);
                all_vectors.push_back(follows.getQueryResult());
                vector<string> followsSatisfied = Utilities::findIntersection(all_vectors);
                for (const string& r : followsSatisfied) {
                    if (find(seen.begin(), seen.end(), make_pair(line, r)) == seen.cend()) {
                        results.find(this->entities[0]->toString())->second.push_back(line);
                        results.find(this->entities[1]->toString())->second.push_back(r);
                        seen.emplace_back(line, r);
                    }
                }
            }
        }
        if (this->entities[0]->toString() == "_" && this->entities[1]->toString() == "_") {
            if (!results.empty()) {
                return ResultTable({ {"True", {""}} });
            }
            else {
                return { {} };
            }
        }
        else if (this->entities[0]->toString() == "_") {
            return ResultTable(results).getColumn(this->entities[1]->toString());
        }
        else if (this->entities[1]->toString() == "_") {
            return ResultTable(results).getColumn(this->entities[0]->toString());
        }
        return ResultTable(results);
    }
    else if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() == -1) {
        auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        int nextLineInt = dynamic_cast<StmtEntity*>(this->entities[1])->getLine();
        string nextLine = to_string(nextLineInt);
        vector<string> followedLines;
        for (Result res : vars) {
            for (const string& line : res.getQueryResult()) {
                Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", line));
                if (Utilities::checkIfPresent(follows.getQueryResult(), nextLine)) {
                    followedLines.push_back(line);
                }
            }
        }
        return ResultTable({ {this->entities[0]->toString(), followedLines} });
    }
    else if (dynamic_cast<StmtEntity*>(this->entities[1])->getLine() == -1) {
        int prevLineInt = dynamic_cast<StmtEntity*>(this->entities[0])->getLine();
        string prevLine = to_string(prevLineInt);
        Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", prevLine));
        auto vars = pkb.getAllDesignEntity(this->entities[1]->getType());
        vector<string> possibleLines;
        for (Result res : vars) {
            for (string l : res.getQueryResult()) {
                possibleLines.push_back(l);
            }
        }
        vector<string> followedLines;
        for (const string& line : possibleLines) {
            if (Utilities::checkIfPresent(follows.getQueryResult(), line)) {
                followedLines.push_back(line);
            }
        }
        return ResultTable({ {this->entities[1]->toString(), followedLines} });
    }
    else {
        int prevLineInt = dynamic_cast<StmtEntity*>(this->entities[0])->getLine();
        string prevLine = to_string(prevLineInt);
        int nextLineInt = dynamic_cast<StmtEntity*>(this->entities[1])->getLine();
        string nextLine = to_string(nextLineInt);
        Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", prevLine));
        if (Utilities::checkIfPresent(follows.getQueryResult(), nextLine)) {
            return ResultTable({ {this->entities[0]->toString(), {this->entities[1]->toString()}} });
        }
        else {
            return ResultTable({ {this->entities[0]->toString(), {}} });
        }
    }
}

tuple<StmtEntity*, StmtEntity*> NextsExpression::generateStmtEntityPair(string arg1, string arg2, SynonymTable synonymTable) {
    StmtEntity* a1;
    StmtEntity* a2;

    if (Utilities::isNumber(arg1)) {
        a1 = new StmtEntity(stoi(arg1));
    }
    else if (arg1 == "_") {
        a1 = new StmtEntity();
    }
    else {
        a1 = dynamic_cast<StmtEntity*>(synonymTable.get(arg1, "stmt"));
        if (a1->getType() == "VARIABLE" || a1->getType() == "PROCEDURE" || a1->getType() == "CONSTANT") {
            throw SemanticException();
        }
    }

    if (Utilities::isNumber(arg2)) {
        a2 = new StmtEntity(stoi(arg2));
    }
    else if (arg2 == "_") {
        a2 = new StmtEntity();
    }
    else {
        a2 = dynamic_cast<StmtEntity*>(synonymTable.get(arg2, "stmt"));
        if (a2->getType() == "VARIABLE" || a2->getType() == "PROCEDURE" || a2->getType() == "CONSTANT") {
            throw SemanticException();
        }
    }

    return std::make_tuple(a1, a2);
}

NextExpression::NextExpression(StmtEntity* s1, StmtEntity* s2) : NextsExpression(s1, s2, "FOLLOWS") {}

string NextExpression::toString() {
    return "Follows(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

NextStarExpression::NextStarExpression(StmtEntity* s1, StmtEntity* s2) : NextsExpression(s1, s2, "FOLLOWSSTAR") {}

string NextStarExpression::toString() {
    return "Follows*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}


vector<NextExpression*> NextExpression::extractNextExpression(const string& query, const SynonymTable& synonymTable) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<NextExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, NEXTREGEX)) {
        tuple<StmtEntity*, StmtEntity*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtEntity* a1 = std::get<0>(stmtEntityPair);
        StmtEntity* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new FollowsExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<NextStarExpression*> NextStarExpression::extractNextStarExpression(const string& query, const SynonymTable& synonymTable) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<NextStarExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, NEXTSTARREGEX)) {
        tuple<StmtEntity*, StmtEntity*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtEntity* a1 = std::get<0>(stmtEntityPair);
        StmtEntity* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new NextStarExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}


bool NextExpression::containsNextExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), NEXTREGEX), std::sregex_iterator()) > 0;
}

bool NextStarExpression::containsNextStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), NEXTSTARREGEX), std::sregex_iterator()) > 0;
}



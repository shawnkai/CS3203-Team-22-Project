//
// Created by Tanishq Sharma on 5/3/23.
//

#include "FAPSExpression.h"

FAPSExpression::FAPSExpression(StmtRef *s1, StmtRef *s2, string pkbAbstraction) : Expression({s1, s2}) {
    this->pkbAbstraction = pkbAbstraction;
}

ResultTable *FAPSExpression::evaluate(PKB pkb) {
    if (this->entities[0]->toString() == this->entities[1]->toString() && !dynamic_cast<WildcardStmtRef *>(this->entities[0])) {
        return new ResultTable({{this->entities[0]->toString(), {}}});
    } else if (!dynamic_cast<StmtEntity *>(this->entities[0]) && !dynamic_cast<StmtEntity *>(this->entities[1])) {
        auto vars1 = pkb.getAllDesignEntity(this->entities[0]->getType());
        auto vars2 = pkb.getAllDesignEntity(this->entities[1]->getType());
        vector<string> possibleLines;
        for (Result res: vars2) {
            for (const string &l: res.getQueryResult()) {
                possibleLines.push_back(l);
            }
        }
        vector<string> followedLines;
        map<string, vector<string>> results = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
        vector<pair<string, string>> seen;
        for (Result res: vars1) {
            for (const string &line: res.getQueryResult()) {
                Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", line));
                vector<vector<string>> all_vectors;
                all_vectors.push_back(possibleLines);
                all_vectors.push_back(follows.getQueryResult());
                vector<string> followsSatisfied = Utilities::findIntersection(all_vectors);
                for (const string &r: followsSatisfied) {
                    if (find(seen.begin(), seen.end(), make_pair(line, r)) == seen.cend()) {
                        results.find(this->entities[0]->toString())->second.push_back(line);
                        results.find(this->entities[1]->toString())->second.push_back(r);
                        seen.emplace_back(line, r);
                    }
                }
            }
        }
        if (dynamic_cast<WildcardStmtRef *>(this->entities[0]) && dynamic_cast<WildcardStmtRef *>(this->entities[1])) {
            if (!results.empty()) {
                return new BooleanTrueTable();
            } else {
                return new BooleanFalseTable();
            }
        } else if (dynamic_cast<WildcardStmtRef *>(this->entities[0])) {
            return (new ResultTable(results))->getColumns({this->entities[1]->toString()});
        } else if (dynamic_cast<WildcardStmtRef *>(this->entities[1])) {
            return (new ResultTable(results))->getColumns({this->entities[0]->toString()});
        }
        return new ResultTable(results);
    } else if (!dynamic_cast<StmtEntity *>(this->entities[0])) {
        auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        int nextLineInt = dynamic_cast<StmtEntity *>(this->entities[1])->getLine();
        string nextLine = to_string(nextLineInt);
        vector<string> followedLines;
        for (Result res: vars) {
            for (const string &line: res.getQueryResult()) {
                Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", line));
                if (Utilities::checkIfPresent(follows.getQueryResult(), nextLine)) {
                    followedLines.push_back(line);
                }
            }
        }
        return new ResultTable({{this->entities[0]->toString(), followedLines}});
    } else if (!dynamic_cast<StmtEntity *>(this->entities[1])) {
        int prevLineInt = dynamic_cast<StmtEntity *>(this->entities[0])->getLine();
        string prevLine = to_string(prevLineInt);
        Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", prevLine));
        auto vars = pkb.getAllDesignEntity(this->entities[1]->getType());
        vector<string> possibleLines;
        for (Result res: vars) {
            for (string l: res.getQueryResult()) {
                possibleLines.push_back(l);
            }
        }
        vector<string> followedLines;
        for (const string &line: possibleLines) {
            if (Utilities::checkIfPresent(follows.getQueryResult(), line)) {
                followedLines.push_back(line);
            }
        }
        return new ResultTable({{this->entities[1]->toString(), followedLines}});
    } else {
        int prevLineInt = dynamic_cast<StmtEntity *>(this->entities[0])->getLine();
        string prevLine = to_string(prevLineInt);
        int nextLineInt = dynamic_cast<StmtEntity *>(this->entities[1])->getLine();
        string nextLine = to_string(nextLineInt);
        Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", prevLine));
        if (Utilities::checkIfPresent(follows.getQueryResult(), nextLine)) {
            return new ResultTable({{this->entities[0]->toString(), {this->entities[1]->toString()}}});
        } else {
            return new BooleanFalseTable();
        }
    }
}

tuple<StmtRef *, StmtRef *> FAPSExpression::generateStmtEntityPair(string arg1, string arg2, SynonymTable synonymTable) {
    StmtRef *a1;
    StmtRef *a2;

    if (Utilities::isNumber(arg1)) {
        a1 = new StmtEntity(stoi(arg1));
    } else if (arg1 == "_") {
        a1 = new WildcardStmtRef();
    } else {
        DesignEntity *temp = synonymTable.get(arg1, "select");
        if (!dynamic_cast<StmtRef *>(temp)) {
            throw SemanticException();
        }
        a1 = dynamic_cast<StmtRef *>(temp);
        if (a1->getType() == "VARIABLE" || a1->getType() == "PROCEDURE" || a1->getType() == "CONSTANT") {
            throw SemanticException();
        }
    }

    if (Utilities::isNumber(arg2)) {
        a2 = new StmtEntity(stoi(arg2));
    } else if (arg2 == "_") {
        a2 = new WildcardStmtRef();
    } else {
        DesignEntity *temp = synonymTable.get(arg2, "select");
        if (!dynamic_cast<StmtRef *>(temp)) {
            throw SemanticException();
        }
        a2 = dynamic_cast<StmtRef *>(temp);
        if (a2->getType() == "VARIABLE" || a2->getType() == "PROCEDURE" || a2->getType() == "CONSTANT") {
            throw SemanticException();
        }
    }

    return std::make_tuple(a1, a2);
}

FollowsExpression::FollowsExpression(StmtRef *s1, StmtRef *s2) : FAPSExpression(s1, s2, "FOLLOWS") {}

string FollowsExpression::toString() {
    return "Follows(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

FollowsStarExpression::FollowsStarExpression(StmtRef *s1, StmtRef *s2) : FAPSExpression(s1, s2, "FOLLOWSSTAR") {}

string FollowsStarExpression::toString() {
    return "Follows*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

ParentExpression::ParentExpression(StmtRef *s1, StmtRef *s2) : FAPSExpression(s1, s2, "PARENT") {}
string ParentExpression::toString() {
    return "Parent(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

ParentStarExpression::ParentStarExpression(StmtRef *s1, StmtRef *s2) : FAPSExpression(s1, s2, "PARENTSTAR") {}
string ParentStarExpression::toString() {
    return "Parent*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

vector<FollowsExpression *> FollowsExpression::extractFollowsExpression(const string &query, const SynonymTable &synonymTable) {
    if (!containsFollowsExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<FollowsExpression *> expressions;

    while (regex_search(searchStart, query.cend(), sm, FOLLOWSREGEX)) {
        tuple<StmtRef *, StmtRef *> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtRef *a1 = std::get<0>(stmtEntityPair);
        StmtRef *a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new FollowsExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<FollowsStarExpression *> FollowsStarExpression::extractFollowsStarExpression(const string &query, const SynonymTable &synonymTable) {
    if (!containsFollowsStarExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<FollowsStarExpression *> expressions;

    while (regex_search(searchStart, query.cend(), sm, FOLLOWSSTARREGEX)) {
        tuple<StmtRef *, StmtRef *> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtRef *a1 = std::get<0>(stmtEntityPair);
        StmtRef *a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new FollowsStarExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<ParentExpression *> ParentExpression::extractParentExpression(const string &query, const SynonymTable &synonymTable) {
    if (!containsParentExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<ParentExpression *> expressions;

    while (regex_search(searchStart, query.cend(), sm, PARENTREGEX)) {
        tuple<StmtRef *, StmtRef *> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtRef *a1 = std::get<0>(stmtEntityPair);
        StmtRef *a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new ParentExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<ParentStarExpression *> ParentStarExpression::extractParentStarExpression(const string &query, const SynonymTable &synonymTable) {
    if (!containsParentStarExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<ParentStarExpression *> expressions;

    while (regex_search(searchStart, query.cend(), sm, PARENTSTARREGEX)) {
        tuple<StmtRef *, StmtRef *> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtRef *a1 = std::get<0>(stmtEntityPair);
        StmtRef *a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new ParentStarExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

bool FollowsExpression::containsFollowsExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), FOLLOWSREGEX), std::sregex_iterator()) > 0;
}

bool FollowsStarExpression::containsFollowsStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), FOLLOWSSTARREGEX), std::sregex_iterator()) > 0;
}

bool ParentExpression::containsParentExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), PARENTREGEX), std::sregex_iterator()) > 0;
}

bool ParentStarExpression::containsParentStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), PARENTSTARREGEX), std::sregex_iterator()) > 0;
}

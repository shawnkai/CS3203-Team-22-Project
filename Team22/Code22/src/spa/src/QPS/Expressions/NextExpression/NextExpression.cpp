#include "NextExpression.h"

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

    map<string, vector<string>> results = { {this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}} };
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

ResultTable* NextStarExpression::evaluate(PKB pkb) {
    return new BooleanFalseTable();
}

NextExpression::NextExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string NextExpression::toString() {
    return "Next(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

NextStarExpression::NextStarExpression(StmtRef* s1, StmtRef* s2) : Expression({s1, s2}) {}

string NextStarExpression::toString() {
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
        tuple<StmtRef*, StmtRef*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtRef* a1 = std::get<0>(stmtEntityPair);
        StmtRef* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new NextExpression(a1, a2));
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
        tuple<StmtRef*, StmtRef*> stmtEntityPair = generateStmtEntityPair(sm.str(1), sm.str(2), synonymTable);

        StmtRef* a1 = std::get<0>(stmtEntityPair);
        StmtRef* a2 = std::get<1>(stmtEntityPair);

        expressions.push_back(new NextStarExpression(a1, a2));
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



//
// Created by Tanishq Sharma on 27/3/23.
//

#include "CallsExpression.h"

CallsExpression::CallsExpression(NamedEntity *caller, NamedEntity *callee) : Expression({caller, callee}) {
}

CallsStarExpression::CallsStarExpression(NamedEntity *caller, NamedEntity *callee) : Expression({caller, callee}) {
}

bool CallsExpression::containsCallsExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), CALLSREGEX), std::sregex_iterator()) > 0;
}

bool CallsStarExpression::containsCallsStarExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), CALLSSTARREGEX), std::sregex_iterator()) > 0;
}

vector<CallsExpression*> CallsExpression::extractCallsExpression(const string& query, SynonymTable synonymTable) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<CallsExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, CALLSREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);

        NamedEntity* a1 = CallsExpression::generateNamedEntity(arg1, synonymTable);
        NamedEntity* a2 = CallsExpression::generateNamedEntity(arg2, synonymTable);

        expressions.push_back(new CallsExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

vector<CallsStarExpression*> CallsStarExpression::extractCallsStarExpression(const string& query, SynonymTable synonymTable) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<CallsStarExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, CALLSSTARREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);

        NamedEntity* a1 = CallsExpression::generateNamedEntity(arg1, synonymTable);
        NamedEntity* a2 = CallsExpression::generateNamedEntity(arg2, synonymTable);

        expressions.push_back(new CallsStarExpression(a1, a2));
        searchStart = sm.suffix().first;
    }
    return expressions;
}

NamedEntity* CallsExpression::generateNamedEntity(string s, SynonymTable synonymTable) {
    NamedEntity* a;

    if (s == "_") {
        a = new WildCardEntity();
    } else if (s.find('\"') != string::npos) {
        a = new NamedEntity("ident", s);
    } else if (!Utilities::isAlphanumericString(s)) {
        throw SyntacticException();
    } else {
        a = dynamic_cast<NamedEntity*>(synonymTable.get(s, "named"));
        if (a->getType() != "PROCEDURE") {
            throw SemanticException();
        }
    }

    return a;
}

string CallsExpression::toString() {
    return "Calls(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

string CallsStarExpression::toString() {
    return "Calls*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

ResultTable CallsExpression::evaluate(PKB pkb) {
    vector<string> possibleCallers;
    vector<string> possibleTargets;
    vector<Result> procs = pkb.getAllDesignEntity("PROCEDURE");
    if (this->entities[0]->getType() == "ident") {
        possibleCallers.push_back(Utilities::removeAllOccurrences(this->entities[0]->toString(), '\"'));
    } else {
        for (Result r : procs) {
            possibleCallers.push_back(r.getQueryEntityName());
        }
    }

    if (this->entities[1]->getType() == "ident") {
        possibleTargets.push_back(Utilities::removeAllOccurrences(this->entities[1]->toString(), '\"'));
    } else {
        for (Result r : procs) {
            possibleTargets.push_back(r.getQueryEntityName());
        }
    }

    vector<string> callers;
    vector<string> targets;
    map<string, vector<string>> resultMap = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
    for (const string& p1 : possibleCallers) {
        Result res = pkb.getDesignAbstraction("CALLS", make_pair("_", p1));
        if (res.getQueryEntityName() == "none") {
            continue;
        }
        vector<string> called;
        for (const string& c : res.getQueryResult()) {
            called.push_back(c);
        }
        vector<vector<string>> temp = {{called, possibleTargets}};
        vector<string> result = Utilities::findIntersection(temp);
        for (const string& r : result) {
            if (!((this->entities[0]->toString() == "_" || this->entities[0]->getType() == "ident")
                  && (this->entities[1]->toString() == "_" || this->entities[1]->getType() == "ident"))
                && this->entities[0]->toString() == this->entities[1]->toString()) {
                if (p1 == r) {
                    ::printf("HERE\n");
                    resultMap.at(this->entities[0]->toString()).push_back(p1);
                } else {
                    continue;
                }
            } else {
                resultMap.at(this->entities[0]->toString()).push_back(p1);
                resultMap.at(this->entities[1]->toString()).push_back(r);
            }
        }
    }

    ResultTable temp(resultMap);

    if (this->entities[0]->toString() == "_" || this->entities[0]->getType() == "ident") {
        resultMap.erase(this->entities[0]->toString());
    }
    if (this->entities[1]->toString() == "_" || this->entities[1]->getType() == "ident") {
        resultMap.erase(this->entities[1]->toString());
    }

    if (resultMap.empty()) {
        if (temp.getSize() > 0) {
            return ResultTable({{"_", {"-"}}});
        }
    }

    return ResultTable(resultMap);
}

ResultTable CallsStarExpression::evaluate(PKB pkb) {
    vector<string> possibleCallers;
    vector<string> possibleTargets;
    vector<Result> procs = pkb.getAllDesignEntity("PROCEDURE");
    if (this->entities[0]->getType() == "ident") {
        possibleCallers.push_back(Utilities::removeAllOccurrences(this->entities[0]->toString(), '\"'));
    } else {
        for (Result r : procs) {
            possibleCallers.push_back(r.getQueryEntityName());
        }
    }

    if (this->entities[1]->getType() == "ident") {
        possibleTargets.push_back(Utilities::removeAllOccurrences(this->entities[1]->toString(), '\"'));
    } else {
        for (Result r : procs) {
            possibleTargets.push_back(r.getQueryEntityName());
        }
    }

    vector<string> callers;
    vector<string> targets;
    map<string, vector<string>> resultMap = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
    for (const string& p1 : possibleCallers) {
        Result res = pkb.getDesignAbstraction("CALLSSTAR", make_pair("_", p1));
        if (res.getQueryEntityName() == "none") {
            continue;
        }
        vector<string> called;
        for (const string& c : res.getQueryResult()) {
            called.push_back(c);
        }
        vector<vector<string>> temp = {{called, possibleTargets}};
        vector<string> result = Utilities::findIntersection(temp);
        for (const string& r : result) {
            if (!((this->entities[0]->toString() == "_" || this->entities[0]->getType() == "ident")
                  && (this->entities[1]->toString() == "_" || this->entities[1]->getType() == "ident"))
                  && this->entities[0]->toString() == this->entities[1]->toString()) {
                if (p1 == r) {
                    ::printf("HERE\n");
                    resultMap.at(this->entities[0]->toString()).push_back(p1);
                } else {
                    continue;
                }
            } else {
                resultMap.at(this->entities[0]->toString()).push_back(p1);
                resultMap.at(this->entities[1]->toString()).push_back(r);
            }
        }
    }

    if ((this->entities[0]->toString() == "_" || this->entities[0]->getType() == "ident")
    && (this->entities[1]->toString() == "_" || this->entities[1]->getType() == "ident")) {
        if (ResultTable(resultMap).getSize() > 0) {
            return ResultTable({{"_", {"-"}}});
        } else {
            return {{}};
        }
    }

    if (this->entities[0]->toString() == "_" || this->entities[0]->getType() == "ident") {
        resultMap.erase(this->entities[0]->toString());
    }
    if (this->entities[1]->toString() == "_" || this->entities[1]->getType() == "ident") {
        resultMap.erase(this->entities[1]->toString());
    }

    return ResultTable(resultMap);
}
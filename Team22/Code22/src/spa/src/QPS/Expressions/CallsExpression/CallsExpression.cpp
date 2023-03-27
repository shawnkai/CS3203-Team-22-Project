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
    return {{}};
}

ResultTable CallsStarExpression::evaluate(PKB pkb) {
    return {{}};
}
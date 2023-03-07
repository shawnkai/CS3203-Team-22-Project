//
// Created by Tanishq Sharma on 5/3/23.
//

#include "UsesExpression.h"

bool UsesExpression::containsUsesExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), USESREGEX), std::sregex_iterator()) > 0;
}

vector<UsesExpression*> UsesExpression::extractUsesExpression(const string& query, SynonymTable synonymTable) {
    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<UsesExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, USESREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);
        ::printf("Arguments: %s, %s\n", arg1.c_str(), arg2.c_str());
        if (Utilities::isNumber(arg1)) {
            auto *a1 = new StmtEntity(stoi(arg1));
            NamedEntity *a2;
            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else if (!Utilities::isAlphanumericString(arg2)) {
                throw SyntacticException();
            } else {
                a2 = dynamic_cast<NamedEntity*>(synonymTable.get(arg2, "named"));
            }
            expressions.push_back(new UsesSExpression(a1, a2));
        } else {
            NamedEntity *a1;

            if (arg1 == "_") {
                throw SemanticException();
            } else if (arg1.find('\"') != string::npos) {
                a1 = new NamedEntity("ident", arg1);
            } else if (!Utilities::isAlphanumericString(arg1)) {
                throw SyntacticException();
            } else {
                a1 = dynamic_cast<NamedEntity*>(synonymTable.get(arg1, "named"));
            }

            NamedEntity *a2;
            if (arg2 == "_") {
                a2 = new WildCardEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else if (!Utilities::isAlphanumericString(arg2)) {
                throw SyntacticException();
            } else {
                a2 = dynamic_cast<NamedEntity*>(synonymTable.get(arg2, "named"));
            }

            if (a1->getType() == "VARIABLE" || a1->getType() == "CONSTANT") {
                throw SemanticException();
            }

            expressions.push_back(new UsesPExpression(a1,  a2));
        }
        searchStart = sm.suffix().first;
    }

    return expressions;
}

ResultTable UsesSExpression::evaluate(PKB pkb) {
    auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
    vector<Result> results;
    for (auto var : vars) {
        results.push_back(pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
    }
    vector<string> result;
    for (auto res : results) {
        bool found = false;
        for (const auto& s : res.getQueryResult()) {
            if (s == to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine())) {
                found = true;
                break;
            }
        }
        if (found) {
            result.push_back(res.getQueryEntityName());
        }
    }
    return ResultTable({{this->entities[0]->toString(), result}});
}

ResultTable UsesPExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        string varName = this->entities[0]->toString();
        varName = Utilities::removeAllOccurrences(varName, '\"');
        Result res = pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), varName));
        if (res.getQueryEntityName() != "none" && !res.getQueryResult().empty()) {
            return ResultTable({{this->entities[1]->toString(), res.getQueryResult()}});
        }
        else {
            return {};
        }
    }
    else {
        bool isFirstWildCard = this->entities[1]->getType() == "WILDCARD";

        vector<Result> vars;

        if (this->entities[0]->getType() == "WILDCARD") {
            auto varResult = pkb.getAllDesignEntity("VARIABLE");
            auto constResult = pkb.getAllDesignEntity("CONSTANT");
            vars.insert(vars.end(), varResult.begin(), varResult.end());
            vars.insert(vars.end(), constResult.begin(), constResult.end());
        } else {
            vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        }

        vector<Result> results;
        for (auto var : vars) {
            if (isFirstWildCard) {
                results.push_back(pkb.getDesignAbstraction("USES", make_pair("STATEMENT", var.getQueryEntityName())));
            } else {
                results.push_back(pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
            }
        }
        map<string, vector<string>> result = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
        int ind = 0;
        for (auto res : results) {
            if ((isFirstWildCard && res.getQueryEntityName() != "none") || res.getQueryEntityType() == "USES:" + dynamic_cast<NamedEntity*>(this->entities[1])->getType()) {
                for (const auto& x : res.getQueryResult()) {
                    result.find(this->entities[1]->toString())->second.push_back(x);
                    result.find(this->entities[0]->toString())->second.push_back(vars[ind].getQueryEntityName());
                }
            }
            ind += 1;
        }
        if (isFirstWildCard) {
            return ResultTable({{this->entities[0]->toString(), result.find(this->entities[0]->toString())->second}});
        }
        return ResultTable(result);
    }
}

UsesExpression::UsesExpression(DesignEntity *target) : Expression({target}) {
    if (target->getType() != "VARIABLE" && target->getType() != "ident" && target->getType() != "WILDCARD") {
        throw SemanticException();
    }
}

UsesSExpression::UsesSExpression(StmtEntity* user, DesignEntity* target) : UsesExpression(target) {
    this->entities.push_back(user);
}

string UsesSExpression::toString() {
    return "Uses(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

UsesPExpression::UsesPExpression(NamedEntity* user, DesignEntity* target) : UsesExpression(target) {
    this->entities.push_back(user);
}

string UsesPExpression::toString() {
    return "Uses(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

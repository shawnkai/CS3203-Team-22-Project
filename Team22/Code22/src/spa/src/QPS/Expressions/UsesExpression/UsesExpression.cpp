//
// Created by Tanishq Sharma on 5/3/23.
//

#include "UsesExpression.h"

bool UsesExpression::containsUsesExpression(string query) {
    return distance(sregex_iterator(query.begin(), query.end(), USESREGEX), std::sregex_iterator()) > 0;
}

vector<UsesExpression*> UsesExpression::extractUsesExpression(const string& query, SynonymTable synonymTable) {
    if (!containsUsesExpression(query)) {
        return {};
    }

    smatch sm;

    string::const_iterator searchStart(query.begin());

    vector<UsesExpression*> expressions;

    while (regex_search(searchStart, query.cend(), sm, USESREGEX)) {
        string arg1 = sm.str(1);
        string arg2 = sm.str(2);

        if (Utilities::isNumber(arg1)) {
            auto *a1 = new StmtEntity(stoi(arg1));
            NamedEntity *a2;

            if (arg2.find('_') != string::npos && arg2 != "_") {
                throw SyntacticException();
            } else if ((arg2[0] == '\"' && arg2[arg2.size() - 1] != '\"') || (arg2[0] != '\"' && arg2[arg2.size() - 1] == '\"')) {
                throw SyntacticException();
            }

            if (arg2 == "_") {
                a2 = new WildcardNamedEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else if (!Utilities::isValidVariableName(arg2)) {
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
            } else if (!Utilities::isValidVariableName(arg1)) {
                throw SyntacticException();
            } else {
                a1 = dynamic_cast<NamedEntity*>(synonymTable.get(arg1, "named"));
                if (a1->getType() == "READ" || a1->getType() == "VARIABLE" || a1->getType() == "CONSTANT") {
                    throw SyntacticException();
                }
            }

            if (arg2.find('_') != string::npos && arg2 != "_") {
                throw SyntacticException();
            } else if ((arg2[0] == '\"' && arg2[arg2.size() - 1] != '\"') || (arg2[0] != '\"' && arg2[arg2.size() - 1] == '\"')) {
                throw SyntacticException();
            }

            NamedEntity *a2;
            if (arg2 == "_") {
                a2 = new WildcardNamedEntity();
            } else if (arg2.find('\"') != string::npos) {
                a2 = new NamedEntity("ident", arg2);
            } else if (!Utilities::isValidVariableName(arg2)) {
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

ResultTable* UsesSExpression::evaluate(PKB pkb) {
    vector<Result> vars;
    if (this->entities[0]->getType() == "WILDCARD") {
        auto varResult = pkb.getAllDesignEntity("VARIABLE");
        vars.insert(vars.end(), varResult.begin(), varResult.end());
    } else if (this->entities[0]->getType() == "ident") {
        vars.push_back(pkb.getDesignEntity("VARIABLE", dynamic_cast<NamedEntity*>(this->entities[0])->getSynonym()));
    } else {
        vars = pkb.getAllDesignEntity(this->entities[0]->getType());
    }

    vector<Result> results;
    for (auto var : vars) {
        results.push_back(pkb.getDesignAbstraction("USES", make_pair("STATEMENT", var.getQueryEntityName())));
    }
    vector<string> result;
    for (auto res: results) {
        bool found = false;
        for (const auto& s: res.getQueryResult()) {
            if (s == to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine())) {
                found = true;
                break;
            }
        }
        if (found) {
            result.push_back(res.getQueryEntityName());
        }
    }
    if (this->entities[0]->getType() == "ident" || this->entities[0]->getType() == "WILDCARD") {
        if (result.empty()) {
            return new BooleanFalseTable();
        } else {
            return new BooleanTrueTable();
        }
    }
    return new ResultTable({{this->entities[0]->toString(), result}});
}

ResultTable* UsesPExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        string type = this->entities[1]->getType();
        if (type == "ident") {
            type = "PROCEDURE";
        }
        string varName = this->entities[0]->toString();
        varName = Utilities::removeAllOccurrences(varName, '\"');
        Result res = pkb.getDesignAbstraction("USES", make_pair(type, varName));
        if (res.getQueryEntityName() != "none" && !res.getQueryResult().empty() && res.toString().find("none") == string::npos) {
            vector<string> ans = res.getQueryResult();
            sort(ans.begin(), ans.end());
            if (this->entities[1]->getType() == "ident"){
                if (Utilities::checkIfPresent(ans, Utilities::removeAllOccurrences(this->entities[1]->toString(), '\"'))) {
                    return new BooleanTrueTable();
                } else {
                    return new BooleanFalseTable();
                }
            }
            ResultTable *temp = new ResultTable({{this->entities[1]->toString(), ans}});

            if (this->entities[1]->getType() == "ident") {
                if (temp->getSize() == 0) {
                    return new BooleanFalseTable();
                } else {
                    return new BooleanTrueTable();
                }
            }
            if (temp->getSize() == 0) {
                return new BooleanFalseTable();
            }
            return temp;
        }
        else {
            return new BooleanFalseTable();
        }
    }
    else {
        vector<Result> vars;

        if (this->entities[0]->getType() == "WILDCARD") {
            auto varResult = pkb.getAllDesignEntity("VARIABLE");
            vars.insert(vars.end(), varResult.begin(), varResult.end());
        } else {
            vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        }

        vector<Result> results;
        string type = this->entities[1]->getType();
        if (type == "CALL") {
            type = "PROCEDURECALL";
        }
        for (auto var : vars) {
            if (this->entities[1]->getType() == "ident") {
                results.push_back(pkb.getDesignAbstraction("USES", make_pair("PROCEDURE", var.getQueryEntityName())));
            } else {
                results.push_back(pkb.getDesignAbstraction("USES", make_pair(type, var.getQueryEntityName())));
            }
        }
       unordered_map<string, vector<string>> result = {{this->entities[0]->toString(), {}}, {this->entities[1]->toString(), {}}};
        int ind = 0;
        string val;
        if (type == "ident") {
            type = "PROCEDURE";
            val = Utilities::removeAllOccurrences(this->entities[1]->toString(), '\"');
        }
        for (auto res : results) {
            if (res.getQueryEntityType() == "USES:" + type) {
                for (const auto& x : res.getQueryResult()) {
                    if (this->entities[1]->getType() == "ident" && x == val) {
                        result.find(this->entities[1]->toString())->second.push_back(x);
                        result.find(this->entities[0]->toString())->second.push_back(vars[ind].getQueryEntityName());
                    } else if (this->entities[1]->getType() != "ident")  {
                        result.find(this->entities[1]->toString())->second.push_back(x);
                        result.find(this->entities[0]->toString())->second.push_back(vars[ind].getQueryEntityName());
                    }

                }
            }
            ind += 1;
        }

        if (this->entities[1]->getType() == "ident") {
            result.erase(this->entities[1]->toString());
        }
        ResultTable *temp = new ResultTable(result);
        if (temp->getSize() == 0) {
            return new BooleanFalseTable();
        }
        return temp;
    }
}

UsesExpression::UsesExpression(DesignEntity *target) : Expression({target}) {
    if (target->getType() != "CONSTANT" && target->getType() != "VARIABLE" && target->getType() != "ident" && target->getType() != "WILDCARD") {
        throw SemanticException();
    }
}

UsesSExpression::UsesSExpression(StmtRef* user, DesignEntity* target) : UsesExpression(target) {
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

//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#include "QPS/Expressions.h"

#include <utility>
#include "PKB/PKB.h"
#include <algorithm>
#include <regex>
#include "Utilities.h"

// Function Definitions

Expression::Expression(vector<DesignEntity*> entities) {
    this->entities = std::move(entities);
}

vector<DesignEntity*> Expression::getAllEntities() {
    return this->entities;
}

SelectExpression::SelectExpression(vector<DesignEntity*> entities, vector<Expression*> conditions) : Expression(std::move(entities)){
    this->conditions = std::move(conditions);
}

string SelectExpression::toString() {
    string res = "Select " + this->entities[0]->toString();

    if (!conditions.empty()) {
        res += " such that";
        for (Expression* e : this->conditions) {
            res += " " + e->toString();
        }
    }
    return res;
}

vector<string> SelectExpression::evaluate(PKB pkb) {
    if (this->conditions.empty()) {
        auto results = pkb.getAllDesignEntity(this->entities[0]->getType());
        vector<string> answer;
        for (auto res : results) {
            answer.push_back(res.getQueryEntityName());
        }
        return answer;
    } else {
        vector<vector<string>> all_results;
        for (Expression *exp : this->conditions) {
            vector<string> res = exp->evaluate(pkb);
            if (!res.empty() && res[0].find("2:", 0) != string::npos) {
                vector<string> modified;
                int chosenIdx = 0;
                if (this->entities[0]->getType() == exp->getAllEntities()[0]->getType()) {
                    chosenIdx = 0;
                } else if (this->entities[0]->getType() == exp->getAllEntities()[1]->getType()) {
                    chosenIdx = 1;
                }
                for (const string& x: res) {
                    size_t ind = x.find(',');
                    string first = x.substr(2, ind - 2);
                    string second = x.substr(ind + 1, x.size() - ind);
                    vector<string> parts = {first, second};
                    if (!Utilities::checkIfPresent(modified, parts[chosenIdx])) {
                        modified.push_back(parts[chosenIdx]);
                    }
                }
                all_results.push_back(modified);
            } else if (!res.empty() && count(res[0].begin(), res[0].end(), ',')) {
                vector<string> modified;
                for (const string& x: res) {
                    size_t ind = x.find(',');
                    string name = x.substr(0, ind);
                    string line = x.substr(ind + 1, x.size() - ind);
                    if (this->entities[0]->getType() == "PROCEDURE" || this->entities[0]->getType() == "VARIABLE"
                    || this->entities[0]->getType() == "CONSTANT") {
                        if (!Utilities::checkIfPresent(modified, name)) {
                            modified.push_back(name);
                        }
                    } else {
                        if (!Utilities::checkIfPresent(modified, line)) {
                            modified.push_back(line);
                        }
                    }
                }
                all_results.push_back(modified);
            } else {
                vector<string> modified;
                for (const string& x: res) {
                    if (!Utilities::checkIfPresent(modified, x)) {
                        modified.push_back(x);
                    }
                }
                all_results.push_back(modified);
            }
        }
        return Utilities::findIntersection(all_results);
    }
}


ModifiesExpression::ModifiesExpression(NamedEntity *target) : Expression({target}) {}


ModifiesSExpression::ModifiesSExpression(StmtEntity *modifier, NamedEntity *target) : ModifiesExpression(target) {
    this->entities.push_back(modifier);
}

string ModifiesSExpression::toString() {
    return "Modifies(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

ModifiesPExpression::ModifiesPExpression(NamedEntity *modifier, NamedEntity *target) : ModifiesExpression(target) {
    this->entities.push_back(modifier);
}

string ModifiesPExpression::toString() {
    return "Modifies(" + this->entities[1]->toString() + ", " + this->entities[0]->toString() + ")";
}

UsesExpression::UsesExpression(DesignEntity *target) : Expression({target}) {}


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

FAPSExpression::FAPSExpression(StmtEntity* s1, StmtEntity* s2, string pkbAbstraction) : Expression({s1, s2}) {
    this->pkbAbstraction = pkbAbstraction;
}

FollowsExpression::FollowsExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "FOLLOWS") {}

string FollowsExpression::toString() {
    return "Follows(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

FollowsStarExpression::FollowsStarExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "FOLLOWSSTAR") {}

string FollowsStarExpression::toString() {
    return "Follows*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

ParentExpression::ParentExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "PARENT") {}
string ParentExpression::toString() {
    return "Parent(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}

ParentStarExpression::ParentStarExpression(StmtEntity* s1, StmtEntity* s2) : FAPSExpression(s1, s2, "PARENTSTAR") {}
string ParentStarExpression::toString() {
    return "Parent*(" + this->entities[0]->toString() + ", " + this->entities[1]->toString() + ")";
}


PatternExpression::PatternExpression(DesignEntity *entity, NamedEntity* p1, string p2) : Expression({entity}) {
    this->p1 = p1;
    this->p2 = std::move(p2);
}

vector<string> ModifiesSExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        string varName = this->entities[0]->toString();
        varName = Utilities::removeAllOccurrences(varName, '\"');
        Result res = pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), varName));
        if (!res.getQueryResult().empty() && Utilities::checkIfPresent(res.getQueryResult(), to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()))) {
            return {res.toString()};
        } else {
            return {""};
        }
    } else {
        auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        vector<Result> results;
        for (auto var : vars) {
            results.push_back(pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
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
        sort(result.begin(), result.end());
        return result;
    }

}

vector<string> ModifiesPExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        string varName = this->entities[0]->toString();
        varName = Utilities::removeAllOccurrences(varName, '\"');
        ::printf("%s\n", this->entities[1]->getType().c_str());
        Result res = pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), varName));
        if (!res.getQueryResult().empty()) {
            vector<string> ans = res.getQueryResult();
            sort(ans.begin(), ans.end());
            return ans;
        } else {
            return {""};
        }
    } else {
        auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        vector<Result> results;
        for (auto var : vars) {
            results.push_back(pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
        }
        vector<string> result;
        for (auto res: results) {
            if (res.getQueryEntityType() == "MODIFIES:" + dynamic_cast<NamedEntity*>(this->entities[1])->getType()) {
                for (const auto& x : res.getQueryResult()) {
                    result.push_back(res.getQueryEntityName() + "," + x);
                }
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
}

vector<string> UsesSExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        Result res = pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), this->entities[0]->toString()));
        if (!res.getQueryResult().empty() && Utilities::checkIfPresent(res.getQueryResult(), to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()))) {
            return {res.toString()};
        }
        else {
            return {};
        }
    }
    else {
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
        return result;
    }
}

vector<string> UsesPExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        Result res = pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), this->entities[0]->toString()));
        if (!res.getQueryResult().empty() && Utilities::checkIfPresent(res.getQueryResult(), to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()))) {
            return {res.toString()};
        }
        else {
            return {};
        }
    }
    else {
        auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        vector<Result> results;
        for (auto var : vars) {
            results.push_back(pkb.getDesignAbstraction("USES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
        }
        vector<string> result;
        for (auto res : results) {
            if (res.getQueryEntityType() == "USES:" + dynamic_cast<NamedEntity*>(this->entities[1])->getType()) {
                for (const auto& x : res.getQueryResult()) {
                    result.push_back(res.getQueryEntityName() + "," + x);
                }
            }
        }
        return result;
    }
}

vector<string> FAPSExpression::evaluate(PKB pkb) {
    if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() == -1 && dynamic_cast<StmtEntity*>(this->entities[1])->getLine() == -1) {
        auto vars1 = pkb.getAllDesignEntity(this->entities[0]->getType());
        auto vars2 = pkb.getAllDesignEntity(this->entities[1]->getType());

        vector<string> possibleLines;
        for (Result res : vars2) {
            for (string l : res.getQueryResult()) {
                possibleLines.push_back(l);
            }
        }
        vector<string> followedLines;
        for (Result res : vars1) {
            for (const string& line : res.getQueryResult()) {
                Result follows = pkb.getDesignAbstraction(this->pkbAbstraction, make_tuple("_", line));
                vector<vector<string>> all_vectors;
                all_vectors.push_back(possibleLines);
                all_vectors.push_back(follows.getQueryResult());
                vector<string> followsSatisfied = Utilities::findIntersection(all_vectors);
                for (const string& r : followsSatisfied) {
                    followedLines.push_back("2:" + line + "," + r);
                }
            }
        }
        return followedLines;
    } else if (dynamic_cast<StmtEntity*>(this->entities[0])->getLine() == -1) {
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
        return followedLines;
    } else if (dynamic_cast<StmtEntity*>(this->entities[1])->getLine() == -1) {
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
        return followedLines;
    }
    return {};
}

string PatternExpression::toString() {
    return "pattern " + this->entities[0]->toString() + "(" + this->p1->getSynonym() + ", " + this->p2 + ")";
}

vector<string> PatternExpression::evaluate(PKB pkb) {
    string prefix_expr = p2;
    prefix_expr = regex_replace(prefix_expr, regex("\\-"), "\\-");
    prefix_expr = regex_replace(prefix_expr, regex("\\+"), "\\+");
    prefix_expr = regex_replace(prefix_expr, regex("\\*"), "\\*");
    prefix_expr = regex_replace(prefix_expr, regex("_"), R"([\w\+\-\*/]*)");
    regex right_expr (prefix_expr);

    if (p1->getSynonym() == "_" || p1->getType() == "VARIABLE") {
        auto key_values = pkb.getAllRightHandExpressions();
        vector<string> results;
        for (auto pattern : key_values) {
            for (const auto& lineno_expression : pattern->getAllRightHandExpressions()) {
                if (regex_match(lineno_expression.second, right_expr)) {
                    if (p1->getSynonym() == "_") {
                        results.push_back(lineno_expression.first);
                    } else {
                        results.push_back(pattern->getLeftHandVariableName());
                    }
                }
            }
        }
        return results;
    } else {
        auto key_values = pkb.getAllRightHandExpressionsOfAVariable(p1->getSynonym());
        vector<string> result;

        for (const auto& pair : key_values) {
            if (regex_match(pair.second, right_expr)) {
                result.push_back(pair.first);
            }
        }
        return result;
    }
}
//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#include "QPS/Expressions.h"

#include <utility>
#include "PKB/PKB.h"
#include <algorithm>

// Utility Functions

vector<string> findIntersection(vector<vector<string>>& all_vectors) {
    vector<string> intersection;
    if (all_vectors.empty()) {
        return intersection;
    }

    sort(all_vectors.begin(), all_vectors.end());
    for (const string& str : all_vectors[0]) {
        bool present = true;
        for (int i = 1; i < all_vectors.size(); i++) {
            if (find(all_vectors[i].begin(), all_vectors[i].end(), str) == all_vectors[i].end()) {
                present = false;
                break;
            }
        }
        if (present) {
            intersection.push_back(str);
        }
    }
    return intersection;
}

// Function Definitions

Expression::Expression(vector<DesignEntity*> entities) {
    this->entities = std::move(entities);
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
            all_results.push_back(exp->evaluate(pkb));
        }
        return findIntersection(all_results);
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

PatternExpression::PatternExpression(DesignEntity *entity, string p1, string p2) : Expression({entity}) {
    this->p1 = std::move(p1);
    this->p2 = std::move(p2);
}

vector<string> ModifiesSExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        string varName = this->entities[0]->toString();
        varName.erase(remove(varName.begin(), varName.end(), '\"'), varName.end());
        Result res = pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), varName));
        if (!res.getQueryResult().empty() && count(res.getQueryResult().begin(), res.getQueryResult().end(), to_string(dynamic_cast<StmtEntity*>(this->entities[1])->getLine()))) {
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
        varName.erase(remove(varName.begin(), varName.end(), '\"'), varName.end());
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
                result.push_back(res.getQueryEntityName());
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
}

vector<string> UsesSExpression::evaluate(PKB pkb) {
    return {};
}

vector<string> UsesPExpression::evaluate(PKB pkb) {
    return {};
}
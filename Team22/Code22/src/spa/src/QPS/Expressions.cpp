//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#include "QPS/Expressions.h"

#include <utility>
#include "PKB/PKB.h"

Expression::Expression(vector<DesignEntity*> entities) {
    this->entities = std::move(entities);
}

SelectExpression::SelectExpression(vector<DesignEntity*> entities, vector<Expression*> conditions) : Expression(std::move(entities)){
    this->conditions = std::move(conditions);
}

string SelectExpression::toString() {
    string res = "Select " + this->entities[0]->toString();

    if (not conditions.empty()) {
        res += " such that";
        for (Expression* e : this->conditions) {
            res += " " + e->toString();
        }
    }
    return res;
}

string SelectExpression::evaluate(PKB pkb) {
    if (this->conditions.empty()) {
        auto results = pkb.getAllDesignEntity(this->entities[0]->getType());
        string answer;
        for (auto res : results) {
            answer += res.getQueryEntityName();
            answer += ", ";
        }
        answer.pop_back();
        answer.pop_back();
        return answer;
    } else {
        Expression *exp = this->conditions[0];
        return exp->evaluate(pkb);
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

string ModifiesSExpression::evaluate(PKB pkb) {
    if (this->entities[0]->getType() == "ident") {
        return pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), this->entities[0]->toString())).toString();
    } else {
        auto vars = pkb.getAllDesignEntity(this->entities[0]->getType());
        vector<Result> results;
        for (auto var : vars) {
            results.push_back(pkb.getDesignAbstraction("MODIFIES", make_pair(this->entities[1]->getType(), var.getQueryEntityName())));
        }
        string result;
        for (auto res: results) {
            result += res.getQueryEntityName() + ", ";
        }
        result.pop_back();
        result.pop_back();
        return result;
    }

}

string ModifiesPExpression::evaluate(PKB pkb) {
    return Result("", "", vector<string>()).toString();
}

string UsesSExpression::evaluate(PKB pkb) {
    return Result("", "", vector<string>()).toString();
}

string UsesPExpression::evaluate(PKB pkb) {
    return Result("", "", vector<string>()).toString();
}
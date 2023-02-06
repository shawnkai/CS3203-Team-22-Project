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

Result SelectExpression::evaluate(PKB pkb) {
    if (this->conditions.empty()) {
        return pkb.getDesignEntity(this->entities[0]->getType(), this->entities[0]->toString());
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

Result ModifiesSExpression::evaluate(PKB pkb) {
    return pkb.getDesignAbstraction("MODIFIES", make_tuple(this->entities[0]->getType(), this->entities[0]->toString()));
}

Result ModifiesPExpression::evaluate(PKB pkb) {
    return Result("", "", vector<string>());
}

Result UsesSExpression::evaluate(PKB pkb) {
    return Result("", "", vector<string>());
}

Result UsesPExpression::evaluate(PKB pkb) {
    return Result("", "", vector<string>());
}
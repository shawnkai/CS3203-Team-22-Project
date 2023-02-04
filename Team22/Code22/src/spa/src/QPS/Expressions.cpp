//
// Created by Atin Sakkeer Hussain on 03/02/2023.
//

#include "QPS/Expressions.h"

#include <utility>
#include "PKB/PKB.h"

PKB pkb;

Expression::Expression(vector<DesignEntity> entities) {
    this->entities = std::move(entities);
}

Result Expression::evaluate() {
    vector<string> empty;
    Result emptyResult(empty);
    return emptyResult;
}

SelectExpression::SelectExpression(vector<DesignEntity> entities, vector<Expression> conditions) : Expression(entities){
    this->conditions = std::move(conditions);
}

Result SelectExpression::evaluate() {
    if (this->conditions.empty()) {
        return pkb.getDesignEntity(entities[0].getType());
    }
    vector<string> empty;
    Result emptyResult(empty);
    return emptyResult;
}


ModifiesExpression::ModifiesExpression(NamedEntity target) : Expression({std::move(target)}) {}


ModifiesSExpression::ModifiesSExpression(StmtEntity modifier, NamedEntity target) : ModifiesExpression(std::move(target)) {
    this->entities.push_back(std::move(modifier));
}

ModifiesPExpression::ModifiesPExpression(NamedEntity modifier, NamedEntity target) : ModifiesExpression(std::move(target)) {
    this->entities.push_back(std::move(modifier));
}


UsesExpression::UsesExpression(DesignEntity target) : Expression({std::move(target)}) {}


UsesSExpression::UsesSExpression(StmtEntity user, DesignEntity target) : UsesExpression(target) {
    this->entities.push_back(std::move(user));
}

UsesPExpression::UsesPExpression(NamedEntity user, DesignEntity target) : UsesExpression(target) {
    this->entities.push_back(std::move(user));
}

Result ModifiesSExpression::evaluate() {
    return Result(vector<string>());
}

Result ModifiesPExpression::evaluate() {
    return Result(vector<string>());
}

Result UsesSExpression::evaluate() {
    return Result(vector<string>());
}

Result UsesPExpression::evaluate() {
    return Result(vector<string>());
}
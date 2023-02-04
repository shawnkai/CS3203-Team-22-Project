//
// Created by Atin Sakkeer Hussain on 01/02/2023.
//

#ifndef SPA_EXPRESSIONS_H
#define SPA_EXPRESSIONS_H

#include <string>
#include <utility>
#include <vector>
#include "QPS/Entities.h"
#include "Result.h"

using namespace std;

class Expression {
    virtual Result evaluate(){
        vector<string> empty;
        Result emptyResult(empty);
        return emptyResult;
    };

    protected:
        vector<DesignEntity> entities;

    public:
        explicit Expression();
};


class SelectExpression : public Expression {
private:
    vector<Expression> conditions;

public:
    explicit SelectExpression(vector<Expression> conditions);

    Result evaluate() override;

};


//Modifies Expression Classes
class ModifiesExpression : public Expression {

public:
    explicit ModifiesExpression(NamedEntity target);
};

class ModifiesSExpression : public ModifiesExpression {
private: 
    StmtEntity modifier;

public:
    explicit ModifiesSExpression(StmtEntity modifier);

    Result evaluate() override;
};

class ModifiesPExpression : public ModifiesExpression {
private:
    NamedEntity modifier;

public:
    explicit ModifiesPExpression(NamedEntity modifier);

    Result evaluate() override;
};


//Uses expression classes
class UsesExpression : public Expression {
public:
    explicit UsesExpression(DesignEntity target);
};

class UsesSExpression : public UsesExpression {
private:
    StmtEntity user;

public:
    explicit UsesSExpression(StmtEntity user);

    Result evaluate() override;
};

class UsesPExpression : public UsesExpression {
private:
    NamedEntity user;

public:
    explicit UsesPExpression(NamedEntity user);

    Result evaluate() override;
};


#endif //SPA_EXPRESSIONS_H

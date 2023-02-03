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

class Expression {
    virtual Result evaluate() = 0;
};


class SelectExpression : Expression {
private:
    DesignEntity entity;

public:
    SelectExpression(DesignEntity entity);

    Result evaluate() override;

};

#endif //SPA_EXPRESSIONS_H

//
// Created by Jai Lulla  on 3/2/23.
//

#pragma once

#ifndef SPA_VARIABLE_H
#define SPA_VARIABLE_H

#include <iostream>

#include "DesignEntity.h"

using namespace std;

class Variable: public DesignEntity {
public:
    explicit Variable(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_VARIABLE_H

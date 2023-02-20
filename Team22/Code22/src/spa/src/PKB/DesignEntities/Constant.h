//
// Created by Jai Lulla  on 9/2/23.
//

#pragma once

#ifndef SPA_CONSTANT_H
#define SPA_CONSTANT_H

#include <iostream>

#include "DesignEntity.h"

using namespace std;

class Constant: public DesignEntity {
public:
    explicit Constant(tuple<string, string> entityDetails);

    string getTypeOfEntity() override;
};

#endif //SPA_CONSTANT_H

//
// Created by Jai Lulla  on 17/2/23.
//

#pragma once

#ifndef SPA_PARENT_H
#define SPA_PARENT_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class Parent: public DesignAbstraction {
public:
    explicit Parent(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_PARENT_H

//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_MODIFIES_H
#define SPA_MODIFIES_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class Modifies : public DesignAbstraction {
public:
    explicit Modifies(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif//SPA_MODIFIES_H

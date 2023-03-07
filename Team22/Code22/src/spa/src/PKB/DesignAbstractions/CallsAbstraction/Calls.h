//
// Created by Jai Lulla  on 6/3/23.
//

#pragma once

#ifndef SPA_CALLS_H
#define SPA_CALLS_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class Calls: public DesignAbstraction {
public:
    explicit Calls(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_CALLS_H

//
// Created by Jai Lulla  on 11/2/23.
//

#pragma once

#ifndef SPA_USES_H
#define SPA_USES_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class Uses: public DesignAbstraction {
public:
    explicit Uses(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_USES_H

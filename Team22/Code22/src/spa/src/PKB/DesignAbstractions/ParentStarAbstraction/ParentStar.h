//
// Created by Jai Lulla  on 17/2/23.
//

#pragma once

#ifndef SPA_PARENTSTAR_H
#define SPA_PARENTSTAR_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class ParentStar: public DesignAbstraction {
public:
    explicit ParentStar(tuple<string, string, string> abstractionDetails);

    string getTypeOfAbstraction() override;
};

#endif //SPA_PARENTSTAR_H

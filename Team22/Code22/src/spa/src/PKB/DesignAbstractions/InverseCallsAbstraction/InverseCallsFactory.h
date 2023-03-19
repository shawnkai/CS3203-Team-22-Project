//
// Created by Jai Lulla  on 17/3/23.
//

#pragma once

#ifndef SPA_INVERSECALLSFACTORY_H
#define SPA_INVERSECALLSFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class InverseCallsFactory {
public:
    static DesignAbstraction* createInverseCallsAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif //SPA_INVERSECALLSFACTORY_H

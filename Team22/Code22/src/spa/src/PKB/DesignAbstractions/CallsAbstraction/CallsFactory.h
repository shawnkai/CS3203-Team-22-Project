//
// Created by Jai Lulla  on 6/3/23.
//

#pragma once

#ifndef SPA_CALLSFACTORY_H
#define SPA_CALLSFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class CallsFactory {
public:
    static DesignAbstraction* createCallsAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif //SPA_CALLSFACTORY_H

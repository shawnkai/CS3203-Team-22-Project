//
// Created by Jai Lulla  on 7/3/23.
//

#pragma once

#ifndef SPA_CALLSSTARFACTORY_H
#define SPA_CALLSSTARFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class CallsStarFactory {
public:
    static DesignAbstraction* createCallsStarAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif //SPA_CALLSSTARFACTORY_H

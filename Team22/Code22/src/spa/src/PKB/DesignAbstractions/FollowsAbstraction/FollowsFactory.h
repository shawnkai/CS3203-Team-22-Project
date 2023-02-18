//
// Created by Jai Lulla  on 16/2/23.
//

#pragma once

#ifndef SPA_FOLLOWSFACTORY_H
#define SPA_FOLLOWSFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class FollowsFactory {
public:
    static DesignAbstraction* createFollowsAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif //SPA_FOLLOWSFACTORY_H

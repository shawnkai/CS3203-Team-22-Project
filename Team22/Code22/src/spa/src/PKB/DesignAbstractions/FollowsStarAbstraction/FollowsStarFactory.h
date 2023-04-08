//
// Created by Jai Lulla  on 16/2/23.
//

#pragma once

#ifndef SPA_FOLLOWSSTARFACTORY_H
#define SPA_FOLLOWSSTARFACTORY_H

#include <iostream>


#include "PKB/DesignAbstractions/DesignAbstraction.h"
using namespace std;

class FollowsStarFactory {
public:
    static DesignAbstraction* createFollowsStarAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif //SPA_FOLLOWSSTARFACTORY_H

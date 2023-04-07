//
// Created by Jai Lulla  on 17/2/23.
//

#pragma once

#ifndef SPA_PARENTSTARFACTORY_H
#define SPA_PARENTSTARFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class ParentStarFactory {
public:
    static DesignAbstraction *createParentStarAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif//SPA_PARENTSTARFACTORY_H

//
// Created by Jai Lulla  on 17/2/23.
//

#pragma once

#ifndef SPA_PARENTFACTORY_H
#define SPA_PARENTFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class ParentFactory {
public:
    static DesignAbstraction* createParentAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif //SPA_PARENTFACTORY_H

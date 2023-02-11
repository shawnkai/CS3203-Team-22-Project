//
// Created by Jai Lulla  on 5/2/23.
//

#pragma once

#ifndef SPA_MODIFIESFACTORY_H
#define SPA_MODIFIESFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class ModifiesFactory {
public:
    static DesignAbstraction* createModifiesAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif //SPA_MODIFIESFACTORY_H

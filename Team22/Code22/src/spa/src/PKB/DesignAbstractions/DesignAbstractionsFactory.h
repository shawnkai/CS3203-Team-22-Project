//
// Created by Jai Lulla  on 2/2/23.
//

#pragma once

#ifndef SPA_DESIGNABSTRACTIONSFACTORY_H
#define SPA_DESIGNABSTRACTIONSFACTORY_H

#include <iostream>

#include "DesignAbstraction.h"

using namespace std;

class DesignAbstractionsFactory {
public:
    static DesignAbstraction* createDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails);
};
#endif //SPA_DESIGNABSTRACTIONSFACTORY_H

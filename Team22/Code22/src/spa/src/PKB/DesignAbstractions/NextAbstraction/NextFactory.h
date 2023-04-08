//
// Created by Jai Lulla  on 8/3/23.
//

#pragma once

#ifndef SPA_NEXTFACTORY_H
#define SPA_NEXTFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class NextFactory {
public:
    static DesignAbstraction *createNextAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif//SPA_NEXTFACTORY_H

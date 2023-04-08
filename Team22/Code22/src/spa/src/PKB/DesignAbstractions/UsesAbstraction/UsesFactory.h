//
// Created by Jai Lulla  on 11/2/23.
//

#pragma once

#ifndef SPA_USESFACTORY_H
#define SPA_USESFACTORY_H

#include <iostream>

#include "PKB/DesignAbstractions/DesignAbstraction.h"

using namespace std;

class UsesFactory {
public:
    static DesignAbstraction *createUsesAbstraction(tuple<string, string, string> abstractionDetails);
};

#endif//SPA_USESFACTORY_H

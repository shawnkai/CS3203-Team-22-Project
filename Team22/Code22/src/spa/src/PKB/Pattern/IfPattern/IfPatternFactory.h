//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_IFPATTERNFACTORY_H
#define SPA_IFPATTERNFACTORY_H

#include <iostream>

#include "IfPattern.h"

using namespace std;

class IfPatternFactory {
public:
    static IfPattern *createIfPattern(string lineNumber, string variableName);
};

#endif//SPA_IFPATTERNFACTORY_H

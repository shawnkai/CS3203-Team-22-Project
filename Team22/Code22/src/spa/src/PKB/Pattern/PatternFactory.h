//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_PATTERNFACTORY_H
#define SPA_PATTERNFACTORY_H

#include <iostream>

#include "Pattern.h"

using namespace std;

class PatternFactory {
public:
    static Pattern* createPattern(string patternType, string lineNumber, string variableName);
};

#endif //SPA_PATTERNFACTORY_H

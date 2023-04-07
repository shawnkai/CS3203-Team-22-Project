//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_PATTERNSFACTORY_H
#define SPA_PATTERNSFACTORY_H

#include <iostream>

#include "Pattern.h"

using namespace std;

class PatternsFactory {
public:
    static Pattern* createPattern(string patternType, string lineNumber, string variableName);
};

#endif //SPA_PATTERNSFACTORY_H

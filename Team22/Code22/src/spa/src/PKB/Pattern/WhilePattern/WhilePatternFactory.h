//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_WHILEPATTERNFACTORY_H
#define SPA_WHILEPATTERNFACTORY_H

#include <iostream>

#include "WhilePattern.h"

using namespace std;

class WhilePatternFactory {
public:
    static WhilePattern* createWhilePattern(string lineNumber, string variableName);
};

#endif //SPA_WHILEPATTERNFACTORY_H

//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "WhilePatternFactory.h"

using namespace std;

WhilePattern *WhilePatternFactory::createWhilePattern(string lineNumber, string variableName) {
    return new WhilePattern(lineNumber, variableName);
}

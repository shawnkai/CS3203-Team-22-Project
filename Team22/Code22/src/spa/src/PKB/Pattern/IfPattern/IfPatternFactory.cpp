//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "IfPatternFactory.h"

using namespace std;

IfPattern *IfPatternFactory::createIfPattern(string lineNumber, string variableName) {
    return new IfPattern(lineNumber, variableName);
}

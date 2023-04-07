//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "IfPattern.h"

using namespace std;

IfPattern::IfPattern(string lineNumber, string variableName)
    : Pattern(lineNumber, variableName) {
}

string IfPattern::getTypeOfPattern() {
    return "IF";
}

//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "AssignPatternFactory.h"

using namespace std;

AssignPattern *AssignPatternFactory::createAssignPattern(string leftHandVariableName, string prefixExpression,
                                                         string patternLineNumber) {
    return new AssignPattern(leftHandVariableName, prefixExpression, patternLineNumber);
}

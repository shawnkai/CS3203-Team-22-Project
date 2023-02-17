//
// Created by Jai Lulla  on 16/2/23.
//

#pragma once

#ifndef SPA_ASSIGNPATTERNFACTORY_H
#define SPA_ASSIGNPATTERNFACTORY_H

#include <iostream>

#include "AssignPattern.h"

using namespace std;

class AssignPatternFactory {
public:
    static AssignPattern* createAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber);
};

#endif //SPA_ASSIGNPATTERNFACTORY_H

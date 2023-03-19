//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_IFPATTERN_H
#define SPA_IFPATTERN_H

#include <iostream>
#include <unordered_set>

#include "PKB/Pattern/Pattern.h"

using namespace std;

class IfPattern: public Pattern {
public:
    explicit IfPattern(string lineNumber, string variableName);

    string getTypeOfPattern() override;
};

#endif //SPA_IFPATTERN_H

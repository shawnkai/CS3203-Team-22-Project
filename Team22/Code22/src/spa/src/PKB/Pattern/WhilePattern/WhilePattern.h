//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_WHILEPATTERN_H
#define SPA_WHILEPATTERN_H

#include <iostream>
#include <unordered_set>

#include "PKB/Pattern/Pattern.h"

using namespace std;

class WhilePattern : public Pattern {
public:
    explicit WhilePattern(string lineNumber, string variableName);

    string getTypeOfPattern() override;
};

#endif//SPA_WHILEPATTERN_H

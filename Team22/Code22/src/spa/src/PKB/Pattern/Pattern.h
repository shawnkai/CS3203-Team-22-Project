//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include <iostream>
#include <unordered_set>

using namespace std;

class Pattern {
    string lineNumber;
    unordered_set<string> variableNamesUsed;

public:
    explicit Pattern(string lineNumber, string variableName);

    virtual void addAdditionalVariableOnLine(string variableName);
    virtual string getLineNumber();
    virtual unordered_set<string> getVariableNamesUsed();
    virtual bool isVariableNamePresent(string variableName);

    virtual string getTypeOfPattern() = 0;
};

#endif//SPA_PATTERN_H

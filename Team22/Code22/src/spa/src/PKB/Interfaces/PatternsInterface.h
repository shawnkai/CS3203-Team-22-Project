//
// Created by Jai Lulla  on 30/3/23.
//

#pragma once

#ifndef SPA_PATTERNSINTERFACE_H
#define SPA_PATTERNSINTERFACE_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class PatternsInterface {
public:
    void addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber);
    string getRightHandExpressionOfAVariableOnAParticularLineNumber(string leftHandVariableName,
                                                                    string patternLineNumber);
    unordered_map<string, string> getAllRightHandExpressionsOfAVariable(string leftHandVariableName);
    unordered_map<string, unordered_map<string, string>> getAllRightHandExpressions();

    void addPattern(string patternType, string lineNumber, string variableName);
    bool isVariableUsedInPattern(string patternType, string lineNumber, string variableName);
    unordered_set<string> getAllVariablesUsedInPattern(string patternType, string lineNumber);
};

#endif//SPA_PATTERNSINTERFACE_H

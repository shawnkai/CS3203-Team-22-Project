//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_ASSIGNPATTERN_H
#define SPA_ASSIGNPATTERN_H

#include <iostream>
#include <unordered_map>

using namespace std;

class AssignPattern {
    string leftHandVariableName;
    unordered_map<string, string> rightHandExpressionByLineNumber;

    virtual bool isLineNumberPresent(string patternLineNumber);

public:
    explicit AssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber);

    virtual void addAdditionalRightHandExpression(string patternLineNumber, string prefixExpression);
    virtual string getLeftHandVariableName();
    virtual string getRightHandExpressionByLineNumber(string patternLineNumber);
    virtual unordered_map<string, string> getAllRightHandExpressions();
};

#endif//SPA_ASSIGNPATTERN_H

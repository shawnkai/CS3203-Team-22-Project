//
// Created by Jai Lulla  on 15/2/23.
//

#pragma once

#ifndef SPA_ASSIGNPATTERNDATABASE_H
#define SPA_ASSIGNPATTERNDATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "AssignPattern.h"

using namespace std;

class AssignPatternDatabase {
    unordered_map<string, AssignPattern*> database;

    virtual bool isLeftHandVariablePresentInDatabase(AssignPattern* assignPatternToBeStored);
    virtual bool isLeftHandVariablePresentInDatabase(string leftHandVariableName);
    virtual void addRightHandExpressionForAnExistingVariableInDatabase(AssignPattern* assignPatternToBeStored);

public:

    virtual void addToDatabase(AssignPattern* assignPatternToBeStored);
    virtual string getRightHandExpressionOfAVariableOnAParticularLineNumberFromDatabase(string leftHandVariableName, string patternLineNumber);
    virtual unordered_map<string, string> getAllRightHandExpressionsOfAVariableFromDatabase(string leftHandVariableName);
    virtual vector<AssignPattern*> getAllRightHandExpressionsFromDatabase();
};

#endif //SPA_ASSIGNPATTERNDATABASE_H

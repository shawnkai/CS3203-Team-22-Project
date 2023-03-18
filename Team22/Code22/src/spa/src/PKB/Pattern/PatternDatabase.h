//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_PATTERNDATABASE_H
#define SPA_PATTERNDATABASE_H

#include <iostream>
#include <unordered_map>

#include "Pattern.h"

using namespace std;

class PatternDatabase {
    virtual bool isLineNumberPresent(string lineNumber) = 0;
    virtual void updatePatternInDatabase(Pattern* patternToBeStored) = 0;

public:
    virtual void addToDatabase(Pattern* patternToBeStored) = 0;
    virtual unordered_set<string> getAllVariablesBeingUsed(string lineNumber) = 0;
    virtual bool isVariableNamePresentOnLineNumber(string lineNumber, string variableName) = 0;
};

#endif //SPA_PATTERNDATABASE_H

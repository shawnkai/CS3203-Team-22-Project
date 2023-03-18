//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_IFPATTERNDATABASE_H
#define SPA_IFPATTERNDATABASE_H

#include <iostream>
#include <unordered_map>

#include "IfPattern.h"
#include "PKB/Pattern/PatternDatabase.h"

using namespace std;

class IfPatternDatabase: PatternDatabase {
    unordered_map<string, IfPattern*> database;

    bool isLineNumberPresent(string lineNumber) override;
    void updatePatternInDatabase(Pattern* patternToBeStored) override;

    bool isValidPatternType(Pattern* patternToBeStored);

public:
    void addToDatabase(Pattern* patternToBeStored) override;
    unordered_set<string> getAllVariablesBeingUsed(string lineNumber) override;
    bool isVariableNamePresentOnLineNumber(string lineNumber, string variableName) override;
};

#endif //SPA_IFPATTERNDATABASE_H

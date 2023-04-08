//
// Created by Jai Lulla  on 18/3/23.
//

#pragma once

#ifndef SPA_WHILEPATTERNDATABASE_H
#define SPA_WHILEPATTERNDATABASE_H

#include <iostream>
#include <unordered_map>

#include "PKB/Pattern/PatternDatabase.h"
#include "WhilePattern.h"

using namespace std;

class WhilePatternDatabase : public PatternDatabase {
    unordered_map<string, WhilePattern *> database;

    bool isLineNumberPresent(string lineNumber) override;
    void updatePatternInDatabase(Pattern *patternToBeStored) override;

    bool isValidPatternType(Pattern *patternToBeStored);

public:
    void addToDatabase(Pattern *patternToBeStored) override;
    unordered_set<string> getAllVariablesBeingUsed(string lineNumber) override;
    bool isVariableNamePresentOnLineNumber(string lineNumber, string variableName) override;
};

#endif//SPA_WHILEPATTERNDATABASE_H

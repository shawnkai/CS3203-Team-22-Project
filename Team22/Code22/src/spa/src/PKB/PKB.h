#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Result.h"
#include "Pattern/AssignPattern/AssignPattern.h"

using namespace std;

class PKB {
public:
    void addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails);
    Result getDesignEntity(string entityType, string entityName);
    vector<Result> getAllDesignEntity(string entityType);

    void addDesignEntity(string designEntity, tuple<string, string> entityDetails);
    Result getDesignAbstraction(string abstractionType, tuple<string, string> query);

    void addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber);
    string getRightHandExpressionOfAVariableOnAParticularLineNumber(string leftHandVariableName, string patternLineNumber);
    unordered_map<string, string> getAllRightHandExpressionsOfAVariable(string leftHandVariableName);
    vector<AssignPattern*> getAllRightHandExpressions();
};

#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Result.h"
#include "Pattern/AssignPattern/AssignPattern.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:

	static VarTable* varTable;

    void addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails);
    void addDesignEntity(string designEntity, tuple<string, string> entityDetails);
    Result getDesignAbstraction(string abstractionType, tuple<string, string> query); // string -> Result
    Result getDesignEntity(string entityType, string entityName); // string -> Result
    vector<Result>  getAllDesignEntity(string entityType);
    Result getDesignEntity(string entityType, string entityName, string occurrenceLine);

    void addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber);
    string getRightHandExpressionOfAVariableOnAParticularLineNumber(string leftHandVariableName, string patternLineNumber);
    unordered_map<string, string> getAllRightHandExpressionsOfAVariable(string leftHandVariableName);
    vector<AssignPattern*> getAllRightHandExpressions();
};

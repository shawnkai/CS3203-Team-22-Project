#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>

#include "Result.h"
#include "Pattern/AssignPattern/AssignPattern.h"

using namespace std;

class PKB {
    void clearDesignAbstractionDatabase();
    void clearDesignEntityDatabase();
    void clearAssignPatternDatabase();
    void clearControlFlowGraphDatabase();

public:
    void addDesignEntity(string designEntity, tuple<string, string> entityDetails);
    Result getDesignEntity(string entityType, string entityName);
    vector<Result> getAllDesignEntity(string entityType);
    int getNumberOfDesignEntity(string entityType);

    void addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails);
    Result getDesignAbstraction(string abstractionType, tuple<string, string> query);

    void addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber);
    string getRightHandExpressionOfAVariableOnAParticularLineNumber(string leftHandVariableName, string patternLineNumber);
    unordered_map<string, string> getAllRightHandExpressionsOfAVariable(string leftHandVariableName);
    unordered_map<string, unordered_map<string, string>> getAllRightHandExpressions();

    void addControlFlowGraph(vector<int> topologicallySortedElements, map<int, vector<int>> blockToStatementNumbers, map<int, int> statementNumberToBlock, map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers);
    vector<int> getTopologicallySortedElementsDatabase();
    map<int, vector<int>> getBlockToStatementNumbersDatabase();
    map<int, int> getStatementNumberToBlockDatabase();
    map<int, vector<int>> getBlockToBlockDatabase();
    unordered_set<int> getBlocksWithBackPointersDatabase();

    void clearAllDatabases();
};

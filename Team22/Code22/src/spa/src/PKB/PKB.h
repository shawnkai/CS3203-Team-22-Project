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
    // APIs Related To Design Entities
    void addDesignEntity(string designEntity, tuple<string, string> entityDetails);
    Result getDesignEntity(string entityType, string entityName);
    vector<Result> getAllDesignEntity(string entityType);
    int getNumberOfDesignEntity(string entityType);

    // APIs Related to Design Abstractions
    void addDesignAbstraction(string designAbstraction, tuple<string, string, string> abstractionDetails);
    Result getDesignAbstraction(string abstractionType, tuple<string, string> query);
    // Overloaded APIs, for all except modifies and uses
    void addDesignAbstraction(string designAbstraction, tuple<string, string> abstractionDetails);
    Result getDesignAbstraction(string abstractionType, string query);
    vector<Result> getAllDesignAbstractions(string designAbstractionType, string entityTypeBeingAbstracted);
    unordered_map<string, unordered_set<string>> getAllVariablesCapturedByDesignAbstraction(
            string designAbstractionType, string entityTypeBeingAbstracted);

    // APIs Related to Assign Pattern
    void addAssignPattern(string leftHandVariableName, string prefixExpression, string patternLineNumber);
    string getRightHandExpressionOfAVariableOnAParticularLineNumber(string leftHandVariableName,
                                                                    string patternLineNumber);
    unordered_map<string, string> getAllRightHandExpressionsOfAVariable(string leftHandVariableName);
    vector<AssignPattern*> getAllRightHandExpressions();

    // APIs Related to Control Flow Graph
    void addControlFlowGraph(string procedureName, vector<int> topologicallySortedElements,
                             map<int, vector<int>> blockToStatementNumbers, map<int, int> statementNumberToBlock,
                             map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers);
    vector<int> getTopologicallySortedElementsDatabase(string procedureName);
    map<int, vector<int>> getBlockToStatementNumbersDatabase(string procedureName);
    map<int, int> getStatementNumberToBlockDatabase(string procedureName);
    map<int, vector<int>> getBlockToBlockDatabase(string procedureName);
    unordered_set<int> getBlocksWithBackPointersDatabase(string procedureName);

    // API For Clearing All Databases
    void clearAllDatabases();
};

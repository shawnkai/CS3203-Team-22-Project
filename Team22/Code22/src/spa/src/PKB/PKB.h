#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "PKB/Interfaces/CacheInterface.h"
#include "PKB/Interfaces/ControlFlowGraphInterface.h"
#include "PKB/Interfaces/DesignAbstractionsInterface.h"
#include "PKB/Interfaces/DesignEntitiesInterface.h"
#include "PKB/Interfaces/PatternsInterface.h"

#include "Result.h"

#include "QPS/Evaluator/ResultTable.h"

using namespace std;

class PKB {
    CacheInterface *cacheInterface = new CacheInterface();
    ControlFlowGraphInterface *controlFlowGraphInterface = new ControlFlowGraphInterface();
    DesignAbstractionsInterface *designAbstractionsInterface = new DesignAbstractionsInterface();
    DesignEntitiesInterface *designEntitiesInterface = new DesignEntitiesInterface();
    PatternsInterface *patternsInterface = new PatternsInterface();

    void clearDesignAbstractionDatabase();
    void clearDesignEntityDatabase();
    void clearAssignPatternDatabase();
    void clearControlFlowGraphDatabase();
    void clearPatternDatabase();

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
    unordered_map<string, unordered_map<string, string>> getAllRightHandExpressions();
    
    // APIs Related to If and While Patterns
    void addPattern(string patternType, string lineNumber, string variableName);
    bool isVariableUsedInPattern(string patternType, string lineNumber, string variableName);
    unordered_set<string> getAllVariablesUsedInPattern(string patternType, string lineNumber);

    // APIs Related to Control Flow Graph
    void addControlFlowGraph(string procedureName, vector<int> topologicallySortedElements,
                             unordered_map<int, vector<int>> blockToStatementNumbers,
                             unordered_map<int, int> statementNumberToBlock,
                             unordered_map<int, vector<int>> blockToBlock,
                             unordered_set<int> blocksWithBackPointers);
    vector<int> getTopologicallySortedElementsDatabase(string procedureName);
    unordered_map<int, vector<int>> getBlockToStatementNumbersDatabase(string procedureName);
    unordered_map<int, int> getStatementNumberToBlockDatabase(string procedureName);
    unordered_map<int, vector<int>> getBlockToBlockDatabase(string procedureName);
    unordered_set<int> getBlocksWithBackPointersDatabase(string procedureName);


    // APIs Related To Cache
    void addToCache(string accessKey, ResultTable *resultTable);
    ResultTable *getResultTableFromCache(string accessKey);
    unordered_map<string, ResultTable *> getCacheDatabase();
    void clearCache();

    // API For Clearing All Databases
    void clearAllDatabases(string authenticationKey);
};

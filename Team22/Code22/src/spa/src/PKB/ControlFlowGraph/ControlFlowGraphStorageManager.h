//
// Created by Jai Lulla  on 14/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPHSTORAGEMANAGER_H
#define SPA_CONTROLFLOWGRAPHSTORAGEMANAGER_H

#include <iostream>

#include "TopologicallySortedBlockNumbers.h"
#include "BlockToStatementNumbers.h"
#include "StatementNumberToBlock.h"
#include "BlockToBlock.h"
#include "BlocksWithBackPointers.h"

using namespace std;

class ControlFlowGraphStorageManager {
    static inline TopologicallySortedBlockNumbers* topologicallySortedBlockNumbersDatabase = new TopologicallySortedBlockNumbers();
    static inline BlockToStatementNumbers* blockToStatementNumbersDatabase = new BlockToStatementNumbers();
    static inline StatementNumberToBlock* statementNumberToBlockDatabase = new StatementNumberToBlock();
    static inline BlockToBlock* blockToBlockDatabase = new BlockToBlock();
    static inline BlocksWithBackPointers* blocksWithBackPointersDatabase = new BlocksWithBackPointers();

public:
    static void addToDatabase(vector<int> topologicallySortedBlockNumbers, map<int, vector<int>> blockToStatementNumbers, map<int, int> statementNumberToBlock, map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers);

    static vector<int> getTopologicallySortedBlockNumbersDatabase();
    static map<int, vector<int>> getBlockToStatementNumbersDatabase();
    static map<int, int> getStatementNumberToBlockDatabase();
    static map<int, vector<int>> getBlockToBlockDatabase();
    static unordered_set<int> getBlocksWithBackPointersDatabase();

    static void clearDatabase();
};


#endif //SPA_CONTROLFLOWGRAPHSTORAGEMANAGER_H

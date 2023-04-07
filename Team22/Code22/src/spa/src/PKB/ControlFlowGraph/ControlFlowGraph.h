//
// Created by Jai Lulla  on 16/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPH_H
#define SPA_CONTROLFLOWGRAPH_H

#include <iostream>

#include "BlockToBlock.h"
#include "BlockToStatementNumbers.h"
#include "BlocksWithBackPointers.h"
#include "StatementNumberToBlock.h"
#include "TopologicallySortedBlockNumbers.h"

using namespace std;

class ControlFlowGraph {
    string procedureName;

    TopologicallySortedBlockNumbers *topologicallySortedBlockNumbersDatabase = new TopologicallySortedBlockNumbers();
    BlockToStatementNumbers *blockToStatementNumbersDatabase = new BlockToStatementNumbers();
    StatementNumberToBlock *statementNumberToBlockDatabase = new StatementNumberToBlock();
    BlockToBlock *blockToBlockDatabase = new BlockToBlock();
    BlocksWithBackPointers *blocksWithBackPointersDatabase = new BlocksWithBackPointers();

public:
    explicit ControlFlowGraph(string procedureName, vector<int> topologicallySortedBlockNumbers,
                              unordered_map<int, vector<int>> blockToStatementNumbers,
                              unordered_map<int, int> statementNumberToBlock,
                              unordered_map<int, vector<int>> blockToBlock,
                              unordered_set<int> blocksWithBackPointers);

    string getProcedureName();
    vector<int> getTopologicallySortedBlockNumbersDatabase();
    unordered_map<int, vector<int>> getBlockToStatementNumbersDatabase();
    unordered_map<int, int> getStatementNumberToBlockDatabase();
    unordered_map<int, vector<int>> getBlockToBlockDatabase();
    unordered_set<int> getBlocksWithBackPointersDatabase();

    void updateTopologicallySortedBlockNumbersDatabase(vector<int> newTopologicallySortedBlockNumbersDatabase);
    void updateBlockToStatementNumbersDatabase(unordered_map<int, vector<int>> newBlockToStatementNumbersDatabase);
    void updateStatementNumberToBlockDatabase(unordered_map<int, int> newStatementNumberToBlockDatabase);
    void updateBlockToBlockDatabase(unordered_map<int, vector<int>> newBlockToBlockDatabase);
    void updateBlocksWithBackPointers(unordered_set<int> newBlocksWithBackPointersDatabase);
};

#endif//SPA_CONTROLFLOWGRAPH_H

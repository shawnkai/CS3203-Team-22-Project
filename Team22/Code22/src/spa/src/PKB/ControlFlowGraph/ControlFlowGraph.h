//
// Created by Jai Lulla  on 16/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPH_H
#define SPA_CONTROLFLOWGRAPH_H

#include <iostream>

#include "TopologicallySortedBlockNumbers.h"
#include "BlockToStatementNumbers.h"
#include "StatementNumberToBlock.h"
#include "BlockToBlock.h"
#include "BlocksWithBackPointers.h"

using namespace std;

class ControlFlowGraph {
    string procedureName;

    TopologicallySortedBlockNumbers* topologicallySortedBlockNumbersDatabase = new TopologicallySortedBlockNumbers();
    BlockToStatementNumbers* blockToStatementNumbersDatabase = new BlockToStatementNumbers();
    StatementNumberToBlock* statementNumberToBlockDatabase = new StatementNumberToBlock();
    BlockToBlock* blockToBlockDatabase = new BlockToBlock();
    BlocksWithBackPointers* blocksWithBackPointersDatabase = new BlocksWithBackPointers();

public:
    explicit ControlFlowGraph(string procedureName, vector<int> topologicallySortedBlockNumbers, map<int,
            vector<int>> blockToStatementNumbers, map<int, int> statementNumberToBlock,
            map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers);

    string getProcedureName();
    vector<int> getTopologicallySortedBlockNumbersDatabase();
    map<int, vector<int>> getBlockToStatementNumbersDatabase();
    map<int, int> getStatementNumberToBlockDatabase();
    map<int, vector<int>> getBlockToBlockDatabase();
    unordered_set<int> getBlocksWithBackPointersDatabase();
};

#endif //SPA_CONTROLFLOWGRAPH_H

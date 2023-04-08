//
// Created by Jai Lulla  on 30/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPHINTERFACE_H
#define SPA_CONTROLFLOWGRAPHINTERFACE_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class ControlFlowGraphInterface {
public:
    void addControlFlowGraph(string procedureName, vector<int> topologicallySortedElements,
                             unordered_map<int, vector<int>> blockToStatementNumbers,
                             unordered_map<int, int> statementNumberToBlock,
                             unordered_map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers);
    vector<int> getTopologicallySortedElementsDatabase(string procedureName);
    unordered_map<int, vector<int>> getBlockToStatementNumbersDatabase(string procedureName);
    unordered_map<int, int> getStatementNumberToBlockDatabase(string procedureName);
    unordered_map<int, vector<int>> getBlockToBlockDatabase(string procedureName);
    unordered_set<int> getBlocksWithBackPointersDatabase(string procedureName);
};

#endif//SPA_CONTROLFLOWGRAPHINTERFACE_H

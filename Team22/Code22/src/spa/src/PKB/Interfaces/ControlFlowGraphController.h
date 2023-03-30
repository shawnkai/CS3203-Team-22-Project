//
// Created by Jai Lulla  on 30/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPHCONTROLLER_H
#define SPA_CONTROLFLOWGRAPHCONTROLLER_H

#include <iostream>
#include <map>
#include <vector>
#include <unordered_set>

using namespace std;

class ControlFlowGraphController {
public:
    void addControlFlowGraph(string procedureName, vector<int> topologicallySortedElements,
                             map<int, vector<int>> blockToStatementNumbers, map<int, int> statementNumberToBlock,
                             map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers);
    vector<int> getTopologicallySortedElementsDatabase(string procedureName);
    map<int, vector<int>> getBlockToStatementNumbersDatabase(string procedureName);
    map<int, int> getStatementNumberToBlockDatabase(string procedureName);
    map<int, vector<int>> getBlockToBlockDatabase(string procedureName);
    unordered_set<int> getBlocksWithBackPointersDatabase(string procedureName);
};

#endif //SPA_CONTROLFLOWGRAPHCONTROLLER_H

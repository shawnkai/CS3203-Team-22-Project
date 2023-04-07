//
// Created by Jai Lulla  on 16/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPHFACTORY_H
#define SPA_CONTROLFLOWGRAPHFACTORY_H

#include <iostream>

#include "ControlFlowGraph.h"

using namespace std;

class ControlFlowGraphFactory {
public:
    static ControlFlowGraph* createControlFlowGraph(string procedureName, vector<int> topologicallySortedBlockNumbers,
                                                    unordered_map<int, vector<int>> blockToStatementNumbers,
                                                    unordered_map<int, int> statementNumberToBlock,
                                                    unordered_map<int, vector<int>> blockToBlock,
                                                    unordered_set<int> blocksWithBackPointers);
};

#endif //SPA_CONTROLFLOWGRAPHFACTORY_H

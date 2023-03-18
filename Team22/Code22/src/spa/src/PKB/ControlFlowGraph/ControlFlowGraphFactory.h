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
                                                    map<int, vector<int>> blockToStatementNumbers,
                                                    map<int, int> statementNumberToBlock,
                                                    map<int, vector<int>> blockToBlock,
                                                    unordered_set<int> blocksWithBackPointers);
};

#endif //SPA_CONTROLFLOWGRAPHFACTORY_H

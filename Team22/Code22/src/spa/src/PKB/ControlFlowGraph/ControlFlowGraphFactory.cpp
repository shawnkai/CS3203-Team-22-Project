//
// Created by Jai Lulla  on 16/3/23.
//

#include <iostream>

#include "ControlFlowGraphFactory.h"

using namespace std;

ControlFlowGraph *
ControlFlowGraphFactory::createControlFlowGraph(string procedureName, vector<int> topologicallySortedBlockNumbers,
                                                unordered_map<int, vector<int>> blockToStatementNumbers,
                                                unordered_map<int, int> statementNumberToBlock,
                                                unordered_map<int, vector<int>> blockToBlock,
                                                unordered_set<int> blocksWithBackPointers) {
    return new ControlFlowGraph(procedureName, topologicallySortedBlockNumbers, blockToStatementNumbers,
                                statementNumberToBlock, blockToBlock, blocksWithBackPointers);
}

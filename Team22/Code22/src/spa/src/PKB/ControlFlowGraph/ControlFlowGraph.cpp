//
// Created by Jai Lulla  on 16/3/23.
//

#include <iostream>

#include "ControlFlowGraph.h"

using namespace std;

ControlFlowGraph::ControlFlowGraph(string procedureName, vector<int> topologicallySortedBlockNumbers,
                                   map<int, vector<int>> blockToStatementNumbers, map<int, int> statementNumberToBlock,
                                   map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers) {
    this->procedureName = procedureName;
    this->topologicallySortedBlockNumbersDatabase = new TopologicallySortedBlockNumbers(topologicallySortedBlockNumbers);
    this->blockToStatementNumbersDatabase = new BlockToStatementNumbers(blockToStatementNumbers);
    this->statementNumberToBlockDatabase = new StatementNumberToBlock(statementNumberToBlock);
    this->blockToBlockDatabase = new BlockToBlock(blockToBlock);
    this->blocksWithBackPointersDatabase = new BlocksWithBackPointers(blocksWithBackPointers);
}

string ControlFlowGraph::getProcedureName() {
    return this->procedureName;
}

vector<int> ControlFlowGraph::getTopologicallySortedBlockNumbersDatabase() {
    return this->topologicallySortedBlockNumbersDatabase->getTopologicallySortedBlockNumbersDatabase();
}

map<int, vector<int>> ControlFlowGraph::getBlockToStatementNumbersDatabase() {
    return this->blockToStatementNumbersDatabase->getBlockToStatementNumbersDatabase();
}

map<int, int> ControlFlowGraph::getStatementNumberToBlockDatabase() {
    return this->statementNumberToBlockDatabase->getStatementNumbersToBlockDatabase();
}

map<int, vector<int>> ControlFlowGraph::getBlockToBlockDatabase() {
    return this->blockToBlockDatabase->getBlockToBlockDatabase();
}

unordered_set<int> ControlFlowGraph::getBlocksWithBackPointersDatabase() {
    return this->blocksWithBackPointersDatabase->getBlocksWithBackPointersDatabase();
}

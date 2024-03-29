//
// Created by Jai Lulla  on 16/3/23.
//

#include <iostream>

#include "ControlFlowGraph.h"

using namespace std;

ControlFlowGraph::ControlFlowGraph(string procedureName, vector<int> topologicallySortedBlockNumbers,
                                   unordered_map<int, vector<int>> blockToStatementNumbers,
                                   unordered_map<int, int> statementNumberToBlock,
                                   unordered_map<int, vector<int>> blockToBlock,
                                   unordered_set<int> blocksWithBackPointers) {
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

unordered_map<int, vector<int>> ControlFlowGraph::getBlockToStatementNumbersDatabase() {
    return this->blockToStatementNumbersDatabase->getBlockToStatementNumbersDatabase();
}

unordered_map<int, int> ControlFlowGraph::getStatementNumberToBlockDatabase() {
    return this->statementNumberToBlockDatabase->getStatementNumbersToBlockDatabase();
}

unordered_map<int, vector<int>> ControlFlowGraph::getBlockToBlockDatabase() {
    return this->blockToBlockDatabase->getBlockToBlockDatabase();
}

unordered_set<int> ControlFlowGraph::getBlocksWithBackPointersDatabase() {
    return this->blocksWithBackPointersDatabase->getBlocksWithBackPointersDatabase();
}

void ControlFlowGraph::updateTopologicallySortedBlockNumbersDatabase(
        vector<int> newTopologicallySortedBlockNumbersDatabase) {
    this->topologicallySortedBlockNumbersDatabase->copyTopologicallySortedBlockNumbersDatabase(newTopologicallySortedBlockNumbersDatabase);
}

void ControlFlowGraph::updateBlockToStatementNumbersDatabase(
        unordered_map<int, vector<int>> newBlockToStatementNumbersDatabase) {
    this->blockToStatementNumbersDatabase->copyBlockToStatementNumbersDatabase(newBlockToStatementNumbersDatabase);
}

void ControlFlowGraph::updateStatementNumberToBlockDatabase(
        unordered_map<int, int> newStatementNumberToBlockDatabase) {
    this->statementNumberToBlockDatabase->copyStatementNumberToBlockDatabase(newStatementNumberToBlockDatabase);
}

void ControlFlowGraph::updateBlockToBlockDatabase(
        unordered_map<int, vector<int>> newBlockToBlockDatabase) {
    this->blockToBlockDatabase->copyBlockToBlockDatabase(newBlockToBlockDatabase);
}

void ControlFlowGraph::updateBlocksWithBackPointers(unordered_set<int> newBlocksWithBackPointersDatabase) {
    this->blocksWithBackPointersDatabase->copyBlocksWithBackPointersDatabase(newBlocksWithBackPointersDatabase);
}

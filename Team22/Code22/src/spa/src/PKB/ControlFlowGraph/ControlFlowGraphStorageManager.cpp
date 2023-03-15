//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "ControlFlowGraphStorageManager.h"

using namespace std;

void ControlFlowGraphStorageManager::addToDatabase(vector<int> topologicallySortedBlockNumbers,
                                                   map<int, vector<int>> blockToStatementNumbers,
                                                   map<int, int> statementNumberToBlock,
                                                   map<int, vector<int>> blockToBlock,
                                                   unordered_set<int> blocksWithBackPointers) {
    topologicallySortedBlockNumbersDatabase = new TopologicallySortedBlockNumbers(topologicallySortedBlockNumbers);
    blockToStatementNumbersDatabase = new BlockToStatementNumbers(blockToStatementNumbers);
    statementNumberToBlockDatabase = new StatementNumberToBlock(statementNumberToBlock);
    blockToBlockDatabase = new BlockToBlock(blockToBlock);
    blocksWithBackPointersDatabase = new BlocksWithBackPointers(blocksWithBackPointers);
}

vector<int> ControlFlowGraphStorageManager::getTopologicallySortedBlockNumbersDatabase() {
    return topologicallySortedBlockNumbersDatabase->getTopologicallySortedBlockNumbersDatabase();
}

map<int, vector<int>> ControlFlowGraphStorageManager::getBlockToStatementNumbersDatabase() {
    return blockToStatementNumbersDatabase->getBlockToStatementNumbersDatabase();
}

map<int, int> ControlFlowGraphStorageManager::getStatementNumberToBlockDatabase() {
    return statementNumberToBlockDatabase->getStatementNumbersToBlockDatabase();
}

map<int, vector<int>> ControlFlowGraphStorageManager::getBlockToBlockDatabase() {
    return blockToBlockDatabase->getBlockToBlockDatabase();
}

unordered_set<int> ControlFlowGraphStorageManager::getBlocksWithBackPointersDatabase() {
    return blocksWithBackPointersDatabase->getBlocksWithBackPointersDatabase();
}

void ControlFlowGraphStorageManager::clearDatabase() {
    delete topologicallySortedBlockNumbersDatabase;
    delete blockToStatementNumbersDatabase;
    delete statementNumberToBlockDatabase;
    delete blockToBlockDatabase;
    delete blocksWithBackPointersDatabase;

    topologicallySortedBlockNumbersDatabase = new TopologicallySortedBlockNumbers();
    blockToStatementNumbersDatabase = new BlockToStatementNumbers();
    statementNumberToBlockDatabase = new StatementNumberToBlock();
    blockToBlockDatabase = new BlockToBlock();
    blocksWithBackPointersDatabase = new BlocksWithBackPointers();
}

//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "PKB/ControlFlowGraph/ControlFlowGraphFactory.h"
#include "PKB/ControlFlowGraph/ControlFlowGraphDatabaseManager.h"

#include "ControlFlowGraphInterface.h"

using namespace std;

void ControlFlowGraphInterface::addControlFlowGraph(string procedureName, vector<int> topologicallySortedElements,
                                                    unordered_map<int, vector<int>> blockToStatementNumbers,
                                                    unordered_map<int, int> statementNumberToBlock,
                                                    unordered_map<int, vector<int>> blockToBlock,
                                                    unordered_set<int> blocksWithBackPointers) {
    ControlFlowGraph* controlFlowGraph = ControlFlowGraphFactory::createControlFlowGraph(procedureName,
                                                                                         topologicallySortedElements,
                                                                                         blockToStatementNumbers,
                                                                                         statementNumberToBlock,
                                                                                         blockToBlock,
                                                                                         blocksWithBackPointers);
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase();
    db->addToDatabase(controlFlowGraph);
}

vector<int> ControlFlowGraphInterface::getTopologicallySortedElementsDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase();
    return db->getTopologicallySortedBlockNumbersDatabaseFromDatabase(procedureName);
}

unordered_map<int, vector<int>> ControlFlowGraphInterface::getBlockToStatementNumbersDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase();
    return db->getBlockToStatementNumberDatabaseFromDatabase(procedureName);
}

unordered_map<int, int> ControlFlowGraphInterface::getStatementNumberToBlockDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase();
    return db->getStatementNumberToBlockDatabaseFromDatabase(procedureName);
}

unordered_map<int, vector<int>> ControlFlowGraphInterface::getBlockToBlockDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase();
    return db->getBlockToBlockDatabaseFromDatabase(procedureName);
}

unordered_set<int> ControlFlowGraphInterface::getBlocksWithBackPointersDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase();
    return db->getBlocksWithBackPointersDatabaseFromDatabase(procedureName);
}

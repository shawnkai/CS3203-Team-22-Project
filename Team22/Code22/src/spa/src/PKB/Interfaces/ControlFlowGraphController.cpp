//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "PKB/ControlFlowGraph/ControlFlowGraphFactory.h"
#include "PKB/ControlFlowGraph/ControlFlowGraphDatabaseFactory.h"

#include "ControlFlowGraphController.h"

using namespace std;

void ControlFlowGraphController::addControlFlowGraph(string procedureName, vector<int> topologicallySortedElements,
                              map<int, vector<int>> blockToStatementNumbers, map<int, int> statementNumberToBlock,
                              map<int, vector<int>> blockToBlock, unordered_set<int> blocksWithBackPointers) {
    ControlFlowGraph* controlFlowGraph = ControlFlowGraphFactory::createControlFlowGraph(procedureName,
                                                                                         topologicallySortedElements,
                                                                                         blockToStatementNumbers,
                                                                                         statementNumberToBlock,
                                                                                         blockToBlock,
                                                                                         blocksWithBackPointers);
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseFactory::getControlFlowGraphDatabase();
    db->addToDatabase(controlFlowGraph);
}

vector<int> ControlFlowGraphController::getTopologicallySortedElementsDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseFactory::getControlFlowGraphDatabase();
    return db->getTopologicallySortedBlockNumbersDatabaseFromDatabase(procedureName);
}

map<int, vector<int>> ControlFlowGraphController::getBlockToStatementNumbersDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseFactory::getControlFlowGraphDatabase();
    return db->getBlockToStatementNumberDatabaseFromDatabase(procedureName);
}

map<int, int> ControlFlowGraphController::getStatementNumberToBlockDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseFactory::getControlFlowGraphDatabase();
    return db->getStatementNumberToBlockDatabaseFromDatabase(procedureName);
}

map<int, vector<int>> ControlFlowGraphController::getBlockToBlockDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseFactory::getControlFlowGraphDatabase();
    return db->getBlockToBlockDatabaseFromDatabase(procedureName);
}

unordered_set<int> ControlFlowGraphController::getBlocksWithBackPointersDatabase(string procedureName) {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseFactory::getControlFlowGraphDatabase();
    return db->getBlocksWithBackPointersDatabaseFromDatabase(procedureName);
}

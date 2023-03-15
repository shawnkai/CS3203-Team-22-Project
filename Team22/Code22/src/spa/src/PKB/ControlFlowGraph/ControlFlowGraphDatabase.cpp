//
// Created by Jai Lulla  on 16/3/23.
//

#include <iostream>

#include "ControlFlowGraphDatabase.h"

using namespace std;

void ControlFlowGraphDatabase::addToDatabase(ControlFlowGraph *controlFlowGraph) {
    this->controlFlowGraphDatabase.insert(make_pair(controlFlowGraph->getProcedureName(), controlFlowGraph));
}

bool ControlFlowGraphDatabase::isPresentInDatabase(string procedureName) {
    if ((this->controlFlowGraphDatabase.find(procedureName)) == (this->controlFlowGraphDatabase.end())) {
        return false;
    }

    return true;
}

vector<int> ControlFlowGraphDatabase::getTopologicallySortedBlockNumbersDatabaseFromDatabase(string procedureName) {
    if (this->isPresentInDatabase(procedureName)) {
        auto iterator =  this->controlFlowGraphDatabase.find(procedureName);

        return iterator->second->getTopologicallySortedBlockNumbersDatabase();
    }

    // Empty Vector
    return vector<int> {};
}

map<int, vector<int>> ControlFlowGraphDatabase::getBlockToStatementNumberDatabaseFromDatabase(string procedureName) {
    if (this->isPresentInDatabase(procedureName)) {
        auto iterator =  this->controlFlowGraphDatabase.find(procedureName);

        return iterator->second->getBlockToStatementNumbersDatabase();
    }

    // Empty Map
    return map<int, vector<int>> {};
}

map<int, int> ControlFlowGraphDatabase::getStatementNumberToBlockDatabaseFromDatabase(string procedureName) {
    if (this->isPresentInDatabase(procedureName)) {
        auto iterator =  this->controlFlowGraphDatabase.find(procedureName);

        return iterator->second->getStatementNumberToBlockDatabase();
    }

    // Empty Map
    return map<int, int> {};
}

map<int, vector<int>> ControlFlowGraphDatabase::getBlockToBlockDatabaseFromDatabase(string procedureName) {
    if (this->isPresentInDatabase(procedureName)) {
        auto iterator = this->controlFlowGraphDatabase.find(procedureName);

        return iterator->second->getBlockToBlockDatabase();
    }

    // Empty Map
    return map<int, vector<int>> {};
}

unordered_set<int> ControlFlowGraphDatabase::getBlocksWithBackPointersDatabaseFromDatabase(string procedureName) {
    if (this->isPresentInDatabase(procedureName)) {
        auto iterator = this->controlFlowGraphDatabase.find(procedureName);

        return iterator->second->getBlocksWithBackPointersDatabase();
    }

    // Empty Set
    return unordered_set<int> {};
}

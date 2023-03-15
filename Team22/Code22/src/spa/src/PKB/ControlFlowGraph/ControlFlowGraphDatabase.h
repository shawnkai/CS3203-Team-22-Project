//
// Created by Jai Lulla  on 16/3/23.
//

#pragma once

#ifndef SPA_CONTROLFLOWGRAPHDATABASE_H
#define SPA_CONTROLFLOWGRAPHDATABASE_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "ControlFlowGraph.h"

using namespace std;

class ControlFlowGraphDatabase {
    unordered_map<string, ControlFlowGraph*> controlFlowGraphDatabase;

    bool isPresentInDatabase(string procedureName);

public:
    void addToDatabase(ControlFlowGraph* controlFlowGraph);

    vector<int> getTopologicallySortedBlockNumbersDatabaseFromDatabase(string procedureName);
    map<int, vector<int>> getBlockToStatementNumberDatabaseFromDatabase(string procedureName);
    map<int, int> getStatementNumberToBlockDatabaseFromDatabase(string procedureName);
    map<int, vector<int>> getBlockToBlockDatabaseFromDatabase(string procedureName);
    unordered_set<int> getBlocksWithBackPointersDatabaseFromDatabase(string procedureName);
};

#endif //SPA_CONTROLFLOWGRAPHDATABASE_H

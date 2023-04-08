//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "ControlFlowGraphDatabaseManager.h"

using namespace std;

ControlFlowGraphDatabase *ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase() {
    return controlFlowGraphDatabase;
}

void ControlFlowGraphDatabaseManager::clearDatabase() {
    delete controlFlowGraphDatabase;

    controlFlowGraphDatabase = new ControlFlowGraphDatabase();
}

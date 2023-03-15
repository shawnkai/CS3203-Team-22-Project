//
// Created by Jai Lulla  on 14/3/23.
//

#include <iostream>

#include "ControlFlowGraphDatabaseFactory.h"

using namespace std;

ControlFlowGraphDatabase* ControlFlowGraphDatabaseFactory::getControlFlowGraphDatabase() {
    return controlFlowGraphDatabase;
}

void ControlFlowGraphDatabaseFactory::clearDatabase() {
    delete controlFlowGraphDatabase;

    controlFlowGraphDatabase = new ControlFlowGraphDatabase();
}

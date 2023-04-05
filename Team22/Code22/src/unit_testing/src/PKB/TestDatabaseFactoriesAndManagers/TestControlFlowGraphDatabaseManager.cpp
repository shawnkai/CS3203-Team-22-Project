//
// Created by Jai Lulla  on 5/4/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/ControlFlowGraph/ControlFlowGraphDatabaseManager.h"

using namespace std;

TEST_CASE("Test 1: Get Control Flow Graph Database") {
    ControlFlowGraphDatabase* db = ControlFlowGraphDatabaseManager::getControlFlowGraphDatabase();

    ControlFlowGraphDatabase* cfgdb = dynamic_cast<ControlFlowGraphDatabase*>(db);

    REQUIRE (cfgdb != nullptr);
}

//
// Created by Jai Lulla  on 5/4/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/Pattern/AssignPattern/AssignPatternDatabaseManager.h"

using namespace std;

TEST_CASE("Test 1: Get Assign Pattern Database") {
    AssignPatternDatabase* db = AssignPatternDatabaseManager::getAssignPatternDatabase();

    AssignPatternDatabase* apdb = dynamic_cast<AssignPatternDatabase*>(db);

    REQUIRE (apdb != nullptr);
}

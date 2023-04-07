//
// Created by Jai Lulla  on 5/4/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/Pattern/PatternsDatabaseFactory.h"

using namespace std;

TEST_CASE("Test 1: Get If Pattern Database") {
    PatternDatabase* db = PatternsDatabaseFactory::getPatternDatabase("IF");

    IfPatternDatabase* ipdb = dynamic_cast<IfPatternDatabase*>(db);

    REQUIRE (ipdb != nullptr);
}

TEST_CASE("Test 2: Get While Pattern Database") {
    PatternDatabase* db = PatternsDatabaseFactory::getPatternDatabase("WHILE");

    WhilePatternDatabase* wpdb = dynamic_cast<WhilePatternDatabase*>(db);

    REQUIRE (wpdb != nullptr);
}

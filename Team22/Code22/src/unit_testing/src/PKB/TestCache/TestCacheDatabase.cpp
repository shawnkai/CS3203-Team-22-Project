//
// Created by Jai Lulla  on 30/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: ") {
    PKB pkbTest = PKB();
    pkbTest.addPattern("IF", "1", "a");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("IF", "1");

    REQUIRE(result.size() == 1);
}
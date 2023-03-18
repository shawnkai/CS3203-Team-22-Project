//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of If Pattern") {
    PKB pkbTest = PKB();
    pkbTest.addPattern("IF", "1", "a");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("IF", "1");

    REQUIRE(result.size() == 1);
}

TEST_CASE("Test 2: Test clearAllDatabases() on If Pattern Database") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("IF", "2", "a");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("IF", "2");

    REQUIRE(result.size() == 1);

    pkbTest.clearAllDatabases();

    result = pkbTest.getAllVariablesUsedInPattern("IF", "2");

    REQUIRE(result.size() == 0);
}

TEST_CASE("Test 3: Addition of Multiple Unique Variables in If Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("IF", "3", "a");
    pkbTest.addPattern("IF", "3", "b");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("IF", "3");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 4: Addition of Duplicate Variables in If Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("IF", "4", "a");
    pkbTest.addPattern("IF", "4", "b");
    pkbTest.addPattern("IF", "4", "b");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("IF", "4");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 5: Addition of Same Variables on Different Lines in If Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("IF", "5", "a");
    pkbTest.addPattern("IF", "6", "a");
    pkbTest.addPattern("IF", "6", "b");

    unordered_set<string> resultFive = pkbTest.getAllVariablesUsedInPattern("IF", "5");
    unordered_set<string> resultSix = pkbTest.getAllVariablesUsedInPattern("IF", "6");

    REQUIRE(((resultFive.size() == 1) && (resultSix.size() == 2)));
}

TEST_CASE("Test 6: Check If Variable Is Used In Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("IF", "7", "a");
    pkbTest.addPattern("IF", "7", "b");
    pkbTest.addPattern("IF", "7", "c");

    bool resultA = pkbTest.isVariableUsedInPattern("IF", "7", "a");
    bool resultB = pkbTest.isVariableUsedInPattern("IF", "7", "b");
    bool resultD = pkbTest.isVariableUsedInPattern("IF", "7", "d");

    REQUIRE((resultA && resultB && (!(resultD))));
}

TEST_CASE("Test 7: IF: Creating An Invalid Type Of Pattern", "[!throws][!shouldfail]") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("FAIL", "8", "a");
}

TEST_CASE("Test 8: IF: Calling isVariableUsedInPattern() With Invalid Pattern Type", "[!throws][!shouldfail]") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("IF", "9", "a");
    pkbTest.addPattern("IF", "9", "b");
    pkbTest.addPattern("IF", "9", "c");

    bool resultA = pkbTest.isVariableUsedInPattern("FAIL", "9", "a");
}

TEST_CASE("Test 9: IF: Calling getAllVariablesUsedInPattern() With Invalid Pattern Type", "[!throws][!shouldfail]") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("IF", "10", "a");
    pkbTest.addPattern("IF", "10", "b");
    pkbTest.addPattern("IF", "10", "c");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("FAIL", "10");
}

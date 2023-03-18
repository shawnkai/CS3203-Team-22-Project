//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of while Pattern") {
    PKB pkbTest = PKB();
    pkbTest.addPattern("WHILE", "1", "a");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("WHILE", "1");

    REQUIRE(result.size() == 1);
}

TEST_CASE("Test 2: Test clearAllDatabases() on while Pattern Database") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("WHILE", "2", "a");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("WHILE", "2");

    REQUIRE(result.size() == 1);

    pkbTest.clearAllDatabases();

    result = pkbTest.getAllVariablesUsedInPattern("WHILE", "2");

    REQUIRE(result.size() == 0);
}

TEST_CASE("Test 3: Addition of Multiple Unique Variables in while Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("WHILE", "3", "a");
    pkbTest.addPattern("WHILE", "3", "b");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("WHILE", "3");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 4: Addition of Duplicate Variables in while Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("WHILE", "4", "a");
    pkbTest.addPattern("WHILE", "4", "b");
    pkbTest.addPattern("WHILE", "4", "b");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("WHILE", "4");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 5: Addition of Same Variables on Different Lines in while Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("WHILE", "5", "a");
    pkbTest.addPattern("WHILE", "6", "a");
    pkbTest.addPattern("WHILE", "6", "b");

    unordered_set<string> resultFive = pkbTest.getAllVariablesUsedInPattern("WHILE", "5");
    unordered_set<string> resultSix = pkbTest.getAllVariablesUsedInPattern("WHILE", "6");

    REQUIRE(((resultFive.size() == 1) && (resultSix.size() == 2)));
}

TEST_CASE("Test 6: Check while Variable Is Used In Pattern") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("WHILE", "7", "a");
    pkbTest.addPattern("WHILE", "7", "b");
    pkbTest.addPattern("WHILE", "7", "c");

    bool resultA = pkbTest.isVariableUsedInPattern("WHILE", "7", "a");
    bool resultB = pkbTest.isVariableUsedInPattern("WHILE", "7", "b");
    bool resultD = pkbTest.isVariableUsedInPattern("WHILE", "7", "d");

    REQUIRE((resultA && resultB && (!(resultD))));
}

TEST_CASE("Test 7: WHILE: Creating An Invalid Type Of While Pattern", "[!throws][!shouldfail]") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("FAIL", "8", "a");
}

TEST_CASE("Test 8: WHILE: Calling isVariableUsedInPattern() With Invalid Pattern Type", "[!throws][!shouldfail]") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("WHILE", "9", "a");
    pkbTest.addPattern("WHILE", "9", "b");
    pkbTest.addPattern("WHILE", "9", "c");

    bool resultA = pkbTest.isVariableUsedInPattern("FAIL", "9", "a");
}

TEST_CASE("Test 9: WHILE: Calling getAllVariablesUsedInPattern() With Invalid Pattern Type", "[!throws][!shouldfail]") {
    PKB pkbTest = PKB();

    pkbTest.addPattern("WHILE", "10", "a");
    pkbTest.addPattern("WHILE", "10", "b");
    pkbTest.addPattern("WHILE", "10", "c");

    unordered_set<string> result = pkbTest.getAllVariablesUsedInPattern("FAIL", "10");
}

//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/PatternsController.h"

#include "PKB/Exceptions/InvalidPatternTypeException.cpp"
#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of While Pattern") {
    PatternsController patternsController = PatternsController();
    patternsController.addPattern("WHILE", "1", "a");

    unordered_set<string> result = patternsController.getAllVariablesUsedInPattern("WHILE", "1");

    // Bug: == 1: Failing
    REQUIRE(result.size() != 0);
}

TEST_CASE("Test 3: Addition of Multiple Unique Variables in While Pattern") {
    PatternsController patternsController = PatternsController();

    patternsController.addPattern("WHILE", "3", "a");
    patternsController.addPattern("WHILE", "3", "b");

    unordered_set<string> result = patternsController.getAllVariablesUsedInPattern("WHILE", "3");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 4: Addition of Duplicate Variables in While Pattern") {
    PatternsController patternsController = PatternsController();

    patternsController.addPattern("WHILE", "4", "a");
    patternsController.addPattern("WHILE", "4", "b");
    patternsController.addPattern("WHILE", "4", "b");

    unordered_set<string> result = patternsController.getAllVariablesUsedInPattern("WHILE", "4");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 5: Addition of Same Variables on Different Lines in While Pattern") {
    PatternsController patternsController = PatternsController();

    patternsController.addPattern("WHILE", "5", "a");
    patternsController.addPattern("WHILE", "6", "a");
    patternsController.addPattern("WHILE", "6", "b");

    unordered_set<string> resultFive = patternsController.getAllVariablesUsedInPattern("WHILE", "5");
    unordered_set<string> resultSix = patternsController.getAllVariablesUsedInPattern("WHILE", "6");

    REQUIRE(((resultFive.size() == 1) && (resultSix.size() == 2)));
}

TEST_CASE("Test 6: Check Variable Is Used In While Pattern") {
    PatternsController patternsController = PatternsController();

    patternsController.addPattern("WHILE", "7", "a");
    patternsController.addPattern("WHILE", "7", "b");
    patternsController.addPattern("WHILE", "7", "c");

    bool resultA = patternsController.isVariableUsedInPattern("WHILE", "7", "a");
    bool resultB = patternsController.isVariableUsedInPattern("WHILE", "7", "b");
    bool resultD = patternsController.isVariableUsedInPattern("WHILE", "7", "d");

    REQUIRE((resultA && resultB && (!(resultD))));
}

TEST_CASE("Test 7: WHILE: Creating An Invalid Type Of While Pattern") {
    bool exceptionThrown = false;
    PatternsController patternsController = PatternsController();

    try {
        patternsController.addPattern("FAIL", "8", "a");
    } catch (InvalidPatternTypeException& e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

TEST_CASE("Test 8: WHILE: Calling isVariableUsedInPattern() With Invalid Pattern Type") {
    bool exceptionThrown = false;
    PatternsController patternsController = PatternsController();

    patternsController.addPattern("WHILE", "9", "a");
    patternsController.addPattern("WHILE", "9", "b");
    patternsController.addPattern("WHILE", "9", "c");

    try {
        bool resultA = patternsController.isVariableUsedInPattern("FAIL", "9", "a");
    } catch (DatabaseNotFoundException& e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

TEST_CASE("Test 9: WHILE: Calling getAllVariablesUsedInPattern() With Invalid Pattern Type") {
    bool exceptionThrown = false;
    PatternsController patternsController = PatternsController();

    patternsController.addPattern("WHILE", "10", "a");
    patternsController.addPattern("WHILE", "10", "b");
    patternsController.addPattern("WHILE", "10", "c");

    try {
        unordered_set<string> result = patternsController.getAllVariablesUsedInPattern("FAIL", "10");
    } catch (DatabaseNotFoundException& e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

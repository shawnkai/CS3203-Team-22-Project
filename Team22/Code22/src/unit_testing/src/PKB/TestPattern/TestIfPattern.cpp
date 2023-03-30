//
// Created by Jai Lulla  on 18/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/PatternsController.h"

#include "PKB/Exceptions/InvalidPatternTypeException.cpp"
#include "PKB/Exceptions/DatabaseNotFoundException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of If Pattern") {
    PatternsController patternsControllerTest = PatternsController();
    patternsControllerTest.addPattern("IF", "1", "a");

    unordered_set<string> result = patternsControllerTest.getAllVariablesUsedInPattern("IF", "1");

    REQUIRE(result.size() == 1);
}

TEST_CASE("Test 3: Addition of Multiple Unique Variables in If Pattern") {
    PatternsController patternsControllerTest = PatternsController();

    patternsControllerTest.addPattern("IF", "3", "a");
    patternsControllerTest.addPattern("IF", "3", "b");

    unordered_set<string> result = patternsControllerTest.getAllVariablesUsedInPattern("IF", "3");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 4: Addition of Duplicate Variables in If Pattern") {
    PatternsController patternsControllerTest = PatternsController();

    patternsControllerTest.addPattern("IF", "4", "a");
    patternsControllerTest.addPattern("IF", "4", "b");
    patternsControllerTest.addPattern("IF", "4", "b");

    unordered_set<string> result = patternsControllerTest.getAllVariablesUsedInPattern("IF", "4");

    REQUIRE(result.size() == 2);
}

TEST_CASE("Test 5: Addition of Same Variables on Different Lines in If Pattern") {
    PatternsController patternsControllerTest = PatternsController();

    patternsControllerTest.addPattern("IF", "5", "a");
    patternsControllerTest.addPattern("IF", "6", "a");
    patternsControllerTest.addPattern("IF", "6", "b");

    unordered_set<string> resultFive = patternsControllerTest.getAllVariablesUsedInPattern("IF", "5");
    unordered_set<string> resultSix = patternsControllerTest.getAllVariablesUsedInPattern("IF", "6");

    REQUIRE(((resultFive.size() == 1) && (resultSix.size() == 2)));
}

TEST_CASE("Test 6: Check Variable Is Used In If Pattern") {
    PatternsController patternsControllerTest = PatternsController();

    patternsControllerTest.addPattern("IF", "7", "a");
    patternsControllerTest.addPattern("IF", "7", "b");
    patternsControllerTest.addPattern("IF", "7", "c");

    bool resultA = patternsControllerTest.isVariableUsedInPattern("IF", "7", "a");
    bool resultB = patternsControllerTest.isVariableUsedInPattern("IF", "7", "b");
    bool resultD = patternsControllerTest.isVariableUsedInPattern("IF", "7", "d");

    REQUIRE((resultA && resultB && (!(resultD))));
}

TEST_CASE("Test 7: IF: Creating An Invalid Type Of Pattern") {
    bool exceptionThrown = false;
    PatternsController patternsControllerTest = PatternsController();

    try {
        patternsControllerTest.addPattern("FAIL", "8", "a");
    } catch (InvalidPatternTypeException& e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

TEST_CASE("Test 8: IF: Calling isVariableUsedInPattern() With Invalid Pattern Type") {
    bool exceptionThrown = false;
    PatternsController patternsControllerTest = PatternsController();

    patternsControllerTest.addPattern("IF", "9", "a");
    patternsControllerTest.addPattern("IF", "9", "b");
    patternsControllerTest.addPattern("IF", "9", "c");

    try {
        bool resultA = patternsControllerTest.isVariableUsedInPattern("FAIL", "9", "a");
    } catch (DatabaseNotFoundException& e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

TEST_CASE("Test 9: IF: Calling getAllVariablesUsedInPattern() With Invalid Pattern Type") {
    bool exceptionThrown = false;
    PatternsController patternsControllerTest = PatternsController();

    patternsControllerTest.addPattern("IF", "10", "a");
    patternsControllerTest.addPattern("IF", "10", "b");
    patternsControllerTest.addPattern("IF", "10", "c");

    try {
        unordered_set<string> result = patternsControllerTest.getAllVariablesUsedInPattern("FAIL", "10");
    } catch (DatabaseNotFoundException& e) {
        exceptionThrown = true;
    }

    REQUIRE(exceptionThrown);
}

//
// Created by Jai Lulla  on 15/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation and Retrieval of Control Flow Graph") {
    PKB pkbTest = PKB();

    pkbTest.addControlFlowGraph("test",
                                vector<int> {1},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                map<int, int> {{1, 1}},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                unordered_set<int> {1});

    vector<int> resultOne = pkbTest.getTopologicallySortedElementsDatabase("test");
    map<int, vector<int>> resultTwo = pkbTest.getBlockToStatementNumbersDatabase("test");
    map<int, int> resultThree = pkbTest.getStatementNumberToBlockDatabase("test");
    map<int, vector<int>> resultFour = pkbTest.getBlockToBlockDatabase("test");
    unordered_set<int> resultFive = pkbTest.getBlocksWithBackPointersDatabase("test");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());
}

TEST_CASE("Test 2: Retrieval of Non Existent Control Flow Graph") {
    PKB pkbTest = PKB();

    pkbTest.addControlFlowGraph("test",
                                vector<int> {1},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                map<int, int> {{1, 1}},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                unordered_set<int> {1});

    vector<int> resultOne = pkbTest.getTopologicallySortedElementsDatabase("nonExistent");
    map<int, vector<int>> resultTwo = pkbTest.getBlockToStatementNumbersDatabase("nonExistent");
    map<int, int> resultThree = pkbTest.getStatementNumberToBlockDatabase("nonExistent");
    map<int, vector<int>> resultFour = pkbTest.getBlockToBlockDatabase("nonExistent");
    unordered_set<int> resultFive = pkbTest.getBlocksWithBackPointersDatabase("nonExistent");

    REQUIRE(resultOne.size() == 0);
    REQUIRE(resultTwo.size() == 0);
    REQUIRE(resultThree.size() == 0);
    REQUIRE(resultFour.size() == 0);
    REQUIRE(resultFive.size() == 0);
}

TEST_CASE("Test 3: Retrieval of Control Flow Graph When Multiple Unique Are Present") {
    PKB pkbTest = PKB();

    pkbTest.addControlFlowGraph("testOne",
                                vector<int> {1},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                map<int, int> {{1, 1}},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                unordered_set<int> {1});

    pkbTest.addControlFlowGraph("testTwo",
                                vector<int> {1},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                map<int, int> {{1, 1}},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                unordered_set<int> {1});

    vector<int> resultOne = pkbTest.getTopologicallySortedElementsDatabase("testTwo");
    map<int, vector<int>> resultTwo = pkbTest.getBlockToStatementNumbersDatabase("testTwo");
    map<int, int> resultThree = pkbTest.getStatementNumberToBlockDatabase("testTwo");
    map<int, vector<int>> resultFour = pkbTest.getBlockToBlockDatabase("testTwo");
    unordered_set<int> resultFive = pkbTest.getBlocksWithBackPointersDatabase("testTwo");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());

    resultOne = pkbTest.getTopologicallySortedElementsDatabase("testOne");
    resultTwo = pkbTest.getBlockToStatementNumbersDatabase("testOne");
    resultThree = pkbTest.getStatementNumberToBlockDatabase("testOne");
    resultFour = pkbTest.getBlockToBlockDatabase("testOne");
    resultFive = pkbTest.getBlocksWithBackPointersDatabase("testOne");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());
}

TEST_CASE("Test 4: Retrieval of Control Flow Graph When The Same Procedure Name Is Added Twice With Different Data") {
    PKB pkbTest = PKB();

    pkbTest.addControlFlowGraph("testOne",
                                vector<int> {1},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                map<int, int> {{1, 1}},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                unordered_set<int> {1});

    vector<int> resultOne = pkbTest.getTopologicallySortedElementsDatabase("testOne");
    map<int, vector<int>> resultTwo = pkbTest.getBlockToStatementNumbersDatabase("testOne");
    map<int, int> resultThree = pkbTest.getStatementNumberToBlockDatabase("testOne");
    map<int, vector<int>> resultFour = pkbTest.getBlockToBlockDatabase("testOne");
    unordered_set<int> resultFive = pkbTest.getBlocksWithBackPointersDatabase("testOne");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());

    pkbTest.addControlFlowGraph("testOne",
                                vector<int> {2},
                                map<int, vector<int>> {{2, vector<int> {2}}},
                                map<int, int> {{2, 2}},
                                map<int, vector<int>> {{2, vector<int> {2}}},
                                unordered_set<int> {2});

    resultOne = pkbTest.getTopologicallySortedElementsDatabase("testOne");
    resultTwo = pkbTest.getBlockToStatementNumbersDatabase("testOne");
    resultThree = pkbTest.getStatementNumberToBlockDatabase("testOne");
    resultFour = pkbTest.getBlockToBlockDatabase("testOne");
    resultFive = pkbTest.getBlocksWithBackPointersDatabase("testOne");

    REQUIRE(resultOne[0] == 2);
    REQUIRE(resultTwo[2][0] == 2);
    REQUIRE(resultThree[2] == 2);
    REQUIRE(resultFour[2][0] == 2);
    REQUIRE(resultFive.find(2) != resultFive.end());
}

TEST_CASE("Test 5: Populate With Control Flow Graphs and Call clearAllDatabases() API") {
    PKB pkbTest = PKB();

    pkbTest.addControlFlowGraph("test",
                                vector<int> {1},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                map<int, int> {{1, 1}},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                unordered_set<int> {1});

    pkbTest.addControlFlowGraph("testOne",
                                vector<int> {1},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                map<int, int> {{1, 1}},
                                map<int, vector<int>> {{1, vector<int> {1}}},
                                unordered_set<int> {1});

    pkbTest.clearAllDatabases();

    vector<int> resultOne = pkbTest.getTopologicallySortedElementsDatabase("test");
    map<int, vector<int>> resultTwo = pkbTest.getBlockToStatementNumbersDatabase("test");
    map<int, int> resultThree = pkbTest.getStatementNumberToBlockDatabase("test");
    map<int, vector<int>> resultFour = pkbTest.getBlockToBlockDatabase("test");
    unordered_set<int> resultFive = pkbTest.getBlocksWithBackPointersDatabase("test");

    REQUIRE(resultOne.size() == 0);
    REQUIRE(resultTwo.size() == 0);
    REQUIRE(resultThree.size() == 0);
    REQUIRE(resultFour.size() == 0);
    REQUIRE(resultFive.size() == 0);
}

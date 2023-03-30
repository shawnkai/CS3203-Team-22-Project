//
// Created by Jai Lulla  on 15/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/Interfaces/ControlFlowGraphController.h"

using namespace std;

TEST_CASE("Test 1: Creation and Retrieval of Control Flow Graph") {
    ControlFlowGraphController controlFlowGraphController = ControlFlowGraphController();

    controlFlowGraphController.addControlFlowGraph("test",
                                                   vector<int> {1},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   map<int, int> {{1, 1}},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   unordered_set<int> {1});

    vector<int> resultOne = controlFlowGraphController.getTopologicallySortedElementsDatabase("test");
    map<int, vector<int>> resultTwo = controlFlowGraphController.getBlockToStatementNumbersDatabase("test");
    map<int, int> resultThree = controlFlowGraphController.getStatementNumberToBlockDatabase("test");
    map<int, vector<int>> resultFour = controlFlowGraphController.getBlockToBlockDatabase("test");
    unordered_set<int> resultFive = controlFlowGraphController.getBlocksWithBackPointersDatabase("test");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());
}

TEST_CASE("Test 2: Retrieval of Non Existent Control Flow Graph") {
    ControlFlowGraphController controlFlowGraphController = ControlFlowGraphController();

    controlFlowGraphController.addControlFlowGraph("test",
                                                   vector<int> {1},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   map<int, int> {{1, 1}},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   unordered_set<int> {1});

    vector<int> resultOne = controlFlowGraphController.getTopologicallySortedElementsDatabase("nonExistent");
    map<int, vector<int>> resultTwo = controlFlowGraphController.getBlockToStatementNumbersDatabase("nonExistent");
    map<int, int> resultThree = controlFlowGraphController.getStatementNumberToBlockDatabase("nonExistent");
    map<int, vector<int>> resultFour = controlFlowGraphController.getBlockToBlockDatabase("nonExistent");
    unordered_set<int> resultFive = controlFlowGraphController.getBlocksWithBackPointersDatabase("nonExistent");

    REQUIRE(resultOne.size() == 0);
    REQUIRE(resultTwo.size() == 0);
    REQUIRE(resultThree.size() == 0);
    REQUIRE(resultFour.size() == 0);
    REQUIRE(resultFive.size() == 0);
}

TEST_CASE("Test 3: Retrieval of Control Flow Graph When Multiple Unique Are Present") {
    ControlFlowGraphController controlFlowGraphController = ControlFlowGraphController();

    controlFlowGraphController.addControlFlowGraph("testOne",
                                                   vector<int> {1},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   map<int, int> {{1, 1}},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   unordered_set<int> {1});

    controlFlowGraphController.addControlFlowGraph("testTwo",
                                                   vector<int> {1},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   map<int, int> {{1, 1}},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   unordered_set<int> {1});

    vector<int> resultOne = controlFlowGraphController.getTopologicallySortedElementsDatabase("testTwo");
    map<int, vector<int>> resultTwo = controlFlowGraphController.getBlockToStatementNumbersDatabase("testTwo");
    map<int, int> resultThree = controlFlowGraphController.getStatementNumberToBlockDatabase("testTwo");
    map<int, vector<int>> resultFour = controlFlowGraphController.getBlockToBlockDatabase("testTwo");
    unordered_set<int> resultFive = controlFlowGraphController.getBlocksWithBackPointersDatabase("testTwo");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());

    resultOne = controlFlowGraphController.getTopologicallySortedElementsDatabase("testOne");
    resultTwo = controlFlowGraphController.getBlockToStatementNumbersDatabase("testOne");
    resultThree = controlFlowGraphController.getStatementNumberToBlockDatabase("testOne");
    resultFour = controlFlowGraphController.getBlockToBlockDatabase("testOne");
    resultFive = controlFlowGraphController.getBlocksWithBackPointersDatabase("testOne");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());
}

TEST_CASE("Test 4: Retrieval of Control Flow Graph When The Same Procedure Name Is Added Twice With Different Data") {
    ControlFlowGraphController controlFlowGraphController = ControlFlowGraphController();

    controlFlowGraphController.addControlFlowGraph("testOne",
                                                   vector<int> {1},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   map<int, int> {{1, 1}},
                                                   map<int, vector<int>> {{1, vector<int> {1}}},
                                                   unordered_set<int> {1});

    vector<int> resultOne = controlFlowGraphController.getTopologicallySortedElementsDatabase("testOne");
    map<int, vector<int>> resultTwo = controlFlowGraphController.getBlockToStatementNumbersDatabase("testOne");
    map<int, int> resultThree = controlFlowGraphController.getStatementNumberToBlockDatabase("testOne");
    map<int, vector<int>> resultFour = controlFlowGraphController.getBlockToBlockDatabase("testOne");
    unordered_set<int> resultFive = controlFlowGraphController.getBlocksWithBackPointersDatabase("testOne");

    REQUIRE(resultOne[0] == 1);
    REQUIRE(resultTwo[1][0] == 1);
    REQUIRE(resultThree[1] == 1);
    REQUIRE(resultFour[1][0] == 1);
    REQUIRE(resultFive.find(1) != resultFive.end());

    controlFlowGraphController.addControlFlowGraph("testOne",
                                                   vector<int> {2},
                                                   map<int, vector<int>> {{2, vector<int> {2}}},
                                                   map<int, int> {{2, 2}},
                                                   map<int, vector<int>> {{2, vector<int> {2}}},
                                                   unordered_set<int> {2});

    resultOne = controlFlowGraphController.getTopologicallySortedElementsDatabase("testOne");
    resultTwo = controlFlowGraphController.getBlockToStatementNumbersDatabase("testOne");
    resultThree = controlFlowGraphController.getStatementNumberToBlockDatabase("testOne");
    resultFour = controlFlowGraphController.getBlockToBlockDatabase("testOne");
    resultFive = controlFlowGraphController.getBlocksWithBackPointersDatabase("testOne");

    REQUIRE(resultOne[0] == 2);
    REQUIRE(resultTwo[2][0] == 2);
    REQUIRE(resultThree[2] == 2);
    REQUIRE(resultFour[2][0] == 2);
    REQUIRE(resultFive.find(2) != resultFive.end());
}

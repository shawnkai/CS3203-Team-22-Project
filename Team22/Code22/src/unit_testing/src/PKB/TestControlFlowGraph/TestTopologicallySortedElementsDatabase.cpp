//
// Created by Jai Lulla  on 15/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/ControlFlowGraph/TopologicallySortedBlockNumbers.h"

using namespace std;

TEST_CASE("Test 1: Creating Object With Default Constructor") {
    TopologicallySortedBlockNumbers* topologicallySortedBlockNumbers = new TopologicallySortedBlockNumbers();
    vector<int> database = topologicallySortedBlockNumbers->getTopologicallySortedBlockNumbersDatabase();

    REQUIRE((database.size() == 0));
}

TEST_CASE("Test 2: Creating Object With Parameterised Constructor") {
    vector<int> sampleVector = {1, 2, 3, 4};
    TopologicallySortedBlockNumbers* topologicallySortedBlockNumbers = new TopologicallySortedBlockNumbers(sampleVector);
    vector<int> database = topologicallySortedBlockNumbers->getTopologicallySortedBlockNumbersDatabase();

    REQUIRE((database.size() != 0));
}

TEST_CASE("Test 3: Adding An Individual Block Number") {
    TopologicallySortedBlockNumbers* topologicallySortedBlockNumbers = new TopologicallySortedBlockNumbers();
    topologicallySortedBlockNumbers->addBlockNumber(2);

    vector<int> database = topologicallySortedBlockNumbers->getTopologicallySortedBlockNumbersDatabase();

    REQUIRE((database.size() == 1));
}

TEST_CASE("Test 4: Copying A New Block Numbers Database") {
    TopologicallySortedBlockNumbers* topologicallySortedBlockNumbers = new TopologicallySortedBlockNumbers();
    topologicallySortedBlockNumbers->addBlockNumber(2);

    vector<int> oldDatabase = topologicallySortedBlockNumbers->getTopologicallySortedBlockNumbersDatabase();

    topologicallySortedBlockNumbers->copyTopologicallySortedBlockNumbersDatabase(vector<int>{1, 2, 3});
    vector<int> newDatabase = topologicallySortedBlockNumbers->getTopologicallySortedBlockNumbersDatabase();

    REQUIRE(((oldDatabase.size() == 1) && (newDatabase.size() == 3)));
}

TEST_CASE("Test 5: Clearing Database") {
    TopologicallySortedBlockNumbers* topologicallySortedBlockNumbers = new TopologicallySortedBlockNumbers();
    topologicallySortedBlockNumbers->addBlockNumber(2);

    topologicallySortedBlockNumbers->clearDatabase();

    vector<int> database = topologicallySortedBlockNumbers->getTopologicallySortedBlockNumbersDatabase();

    REQUIRE((database.size() == 0));
}

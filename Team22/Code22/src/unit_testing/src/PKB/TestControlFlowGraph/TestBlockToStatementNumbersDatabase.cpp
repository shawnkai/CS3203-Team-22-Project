//
// Created by Jai Lulla  on 15/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/ControlFlowGraph/BlockToStatementNumbers.h"

using namespace std;

TEST_CASE("Test 1: Creating BlockToStatementNumbers With Default Constructor") {
    BlockToStatementNumbers *blockToStatementNumbers = new BlockToStatementNumbers();
    unordered_map<int, vector<int>> result = blockToStatementNumbers->getBlockToStatementNumbersDatabase();

    REQUIRE(result.size() == 0);
}

TEST_CASE("Test 2: Creating BlockToStatementNumbers With Parameterised Constructor") {
    unordered_map<int, vector<int>> sampleMap;

    sampleMap.insert(make_pair(1, vector<int>{1, 2}));
    sampleMap.insert((make_pair(2, vector<int>{3, 4})));

    BlockToStatementNumbers *blockToStatementNumbers = new BlockToStatementNumbers(sampleMap);
    unordered_map<int, vector<int>> database = blockToStatementNumbers->getBlockToStatementNumbersDatabase();

    REQUIRE((database.size() != 0));
}

TEST_CASE("Test 3: Adding An Individual Statement Number") {
    BlockToStatementNumbers *blockToStatementNumbers = new BlockToStatementNumbers();
    blockToStatementNumbers->addToDatabase(1, vector<int>{1, 2});

    unordered_map<int, vector<int>> database = blockToStatementNumbers->getBlockToStatementNumbersDatabase();

    REQUIRE((database.size() == 1));
}

TEST_CASE("Test 4: Copying A New Block To Statement Numbers Database") {
    BlockToStatementNumbers *blockToStatementNumbers = new BlockToStatementNumbers();
    blockToStatementNumbers->addToDatabase(1, vector<int>{1, 2});

    unordered_map<int, vector<int>> oldDatabase = blockToStatementNumbers->getBlockToStatementNumbersDatabase();

    unordered_map<int, vector<int>> sampleMap;

    sampleMap.insert(make_pair(1, vector<int>{1, 2}));
    sampleMap.insert((make_pair(2, vector<int>{3, 4})));

    blockToStatementNumbers->copyBlockToStatementNumbersDatabase(sampleMap);
    unordered_map<int, vector<int>> newDatabase = blockToStatementNumbers->getBlockToStatementNumbersDatabase();

    REQUIRE(((oldDatabase.size() == 1) && (newDatabase.size() == 2)));
}

TEST_CASE("Test 5: Clearing BlockToStatementNumbers Database") {
    BlockToStatementNumbers *blockToStatementNumbers = new BlockToStatementNumbers();
    blockToStatementNumbers->addToDatabase(1, vector<int>{1, 2});

    blockToStatementNumbers->clearDatabase();

    unordered_map<int, vector<int>> database = blockToStatementNumbers->getBlockToStatementNumbersDatabase();

    REQUIRE((database.size() == 0));
}

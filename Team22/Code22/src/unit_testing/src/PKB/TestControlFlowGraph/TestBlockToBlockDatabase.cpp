//
// Created by Jai Lulla  on 15/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/ControlFlowGraph/BlockToBlock.h"

using namespace std;

TEST_CASE("Test 1: Creating BlockToBlock With Default Constructor") {
    BlockToBlock* blockToBlock = new BlockToBlock();
    map<int, vector<int>> database = blockToBlock->getBlockToBlockDatabase();

    REQUIRE((database.size() == 0));
}

TEST_CASE("Test 2: Creating BlockToBlock With Parameterised Constructor") {
    map<int, vector<int>> sampleMap;
    sampleMap.insert(make_pair(1, vector<int> {1, 2}));
    sampleMap.insert(make_pair(2, vector<int> {3}));

    BlockToBlock* blockToBlock = new BlockToBlock(sampleMap);
    map<int, vector<int>> database = blockToBlock->getBlockToBlockDatabase();

    REQUIRE((database.size() != 0));
}

TEST_CASE("Test 3: Adding An Individual Block Number And Block Number") {
    BlockToBlock* blockToBlock = new BlockToBlock();
    blockToBlock->addToDatabase(1, vector<int> {1});

    map<int, vector<int>> database = blockToBlock->getBlockToBlockDatabase();

    REQUIRE((database.size() == 1));
}

TEST_CASE("Test 4: Copying A New Block Number To Block Database") {
    BlockToBlock* blockToBlock = new BlockToBlock();
    blockToBlock->addToDatabase(1, vector<int> {1});

    map<int, vector<int>> oldDatabase = blockToBlock->getBlockToBlockDatabase();

    map<int, vector<int>> sampleMap;
    sampleMap.insert(make_pair(1, vector<int> {1, 2}));
    sampleMap.insert(make_pair(2, vector<int> {3}));

    blockToBlock->copyBlockToBlockDatabase(sampleMap);

    map<int, vector<int>> newDatabase = blockToBlock->getBlockToBlockDatabase();

    REQUIRE(((oldDatabase.size() == 1) && (newDatabase.size() == 2)));
}

TEST_CASE("Test 5: Clearing BlockToBlock Database") {
    BlockToBlock* blockToBlock = new BlockToBlock();
    blockToBlock->addToDatabase(1, vector<int> {1});

    blockToBlock->clearDatabase();

    map<int, vector<int>> database = blockToBlock->getBlockToBlockDatabase();

    REQUIRE((database.size() == 0));
}

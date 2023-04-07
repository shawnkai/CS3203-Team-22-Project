//
// Created by Jai Lulla  on 15/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/ControlFlowGraph/BlocksWithBackPointers.h"

using namespace std;

TEST_CASE("Test 1: Creating BlocksWithBackPointers With Default Constructor") {
    BlocksWithBackPointers *blocksWithBackPointers = new BlocksWithBackPointers();
    unordered_set<int> database = blocksWithBackPointers->getBlocksWithBackPointersDatabase();

    REQUIRE((database.size() == 0));
}

TEST_CASE("Test 2: Creating BlocksWithBackPointers With Parameterised Constructor") {
    unordered_set<int> sampleSet;
    sampleSet.insert(1);
    sampleSet.insert(2);

    BlocksWithBackPointers *blocksWithBackPointers = new BlocksWithBackPointers(sampleSet);
    unordered_set<int> database = blocksWithBackPointers->getBlocksWithBackPointersDatabase();

    REQUIRE((database.size() != 0));
}

TEST_CASE("Test 3: Adding An Individual Block Number In BlocksWithBackPointers Database") {
    BlocksWithBackPointers *blocksWithBackPointers = new BlocksWithBackPointers();
    blocksWithBackPointers->addToDatabase(1);

    unordered_set<int> database = blocksWithBackPointers->getBlocksWithBackPointersDatabase();

    REQUIRE((database.size() == 1));
}

TEST_CASE("Test 4: Copying A New Block With Back Pointers Database") {
    BlocksWithBackPointers *blocksWithBackPointers = new BlocksWithBackPointers();
    blocksWithBackPointers->addToDatabase(1);

    unordered_set<int> oldDatabase = blocksWithBackPointers->getBlocksWithBackPointersDatabase();

    unordered_set<int> sampleSet;
    sampleSet.insert(1);
    sampleSet.insert(2);

    blocksWithBackPointers->copyBlocksWithBackPointersDatabase(sampleSet);

    unordered_set<int> newDatabase = blocksWithBackPointers->getBlocksWithBackPointersDatabase();

    REQUIRE(((oldDatabase.size() == 1) && (newDatabase.size() == 2)));
}

TEST_CASE("Test 5: Clearing BlocksWithBackPointers Database") {
    BlocksWithBackPointers *blocksWithBackPointers = new BlocksWithBackPointers();
    blocksWithBackPointers->addToDatabase(1);

    blocksWithBackPointers->clearDatabase();

    unordered_set<int> database = blocksWithBackPointers->getBlocksWithBackPointersDatabase();

    REQUIRE((database.size() == 0));
}

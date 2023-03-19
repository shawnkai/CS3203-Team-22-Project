//
// Created by Jai Lulla  on 15/3/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/ControlFlowGraph/StatementNumberToBlock.h"

using namespace std;

TEST_CASE("Test 1: Creating StatementNumberToBlock With Default Constructor") {
    StatementNumberToBlock* statementNumberToBlock = new StatementNumberToBlock();
    map<int, int> database = statementNumberToBlock->getStatementNumbersToBlockDatabase();

    REQUIRE((database.size() == 0));
}

TEST_CASE("Test 2: Creating StatementNumberToBlock With Parameterised Constructor") {
    map<int, int> sampleMap;
    sampleMap.insert(make_pair(1, 1));
    sampleMap.insert(make_pair(2, 1));

    StatementNumberToBlock* statementNumberToBlock = new StatementNumberToBlock(sampleMap);
    map<int, int> database = statementNumberToBlock->getStatementNumbersToBlockDatabase();

    REQUIRE((database.size() != 0));
}

TEST_CASE("Test 3: Adding An Individual Statement Number And Block Number") {
    StatementNumberToBlock* statementNumberToBlock = new StatementNumberToBlock();
    statementNumberToBlock->addToDatabase(1, 1);

    map<int, int> database = statementNumberToBlock->getStatementNumbersToBlockDatabase();

    REQUIRE((database.size() == 1));
}

TEST_CASE("Test 4: Copying A New Statement Number To Block Database") {
    StatementNumberToBlock* statementNumberToBlock = new StatementNumberToBlock();
    statementNumberToBlock->addToDatabase(1, 1);

    map<int, int> oldDatabase = statementNumberToBlock->getStatementNumbersToBlockDatabase();

    map<int, int> sampleMap;
    sampleMap.insert(make_pair(1, 1));
    sampleMap.insert(make_pair(2, 1));

    statementNumberToBlock->copyStatementNumberToBlockDatabase(sampleMap);

    map<int, int> newDatabase = statementNumberToBlock->getStatementNumbersToBlockDatabase();

    REQUIRE(((oldDatabase.size() == 1) && (newDatabase.size() == 2)));
}

TEST_CASE("Test 5: Clearing StatementNumberToBlock Database") {
    StatementNumberToBlock* statementNumberToBlock = new StatementNumberToBlock();
    statementNumberToBlock->addToDatabase(1, 1);

    statementNumberToBlock->clearDatabase();

    map<int, int> database = statementNumberToBlock->getStatementNumbersToBlockDatabase();

    REQUIRE((database.size() == 0));
}

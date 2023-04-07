//
// Created by Jai Lulla  on 7/4/23.
//

#include <iostream>

#include "catch.hpp"

#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Test clearAllDatabases() API With Correct Key") {
    SECTION("Testing Design Entities Database") {
        string accessKey = "CalledForTestingPurposes";

        PKB pkb = PKB();
        pkb.addDesignEntity("PROCEDURE", make_tuple("One", "1"));

        Result expectedResult = Result("PROCEDURE", "One", vector<string> {"1"});
        Result result = pkb.getDesignEntity("PROCEDURE", "One");

        REQUIRE(expectedResult.areEqual(result));

        pkb.clearAllDatabases(accessKey);

        REQUIRE(pkb.getNumberOfDesignEntity("PROCEDURE") == 0);
    }

    SECTION("Testing Design Abstractions Database") {
        string accessKey = "CalledForTestingPurposes";

        PKB pkb = PKB();
        pkb.addDesignAbstraction("FOLLOWS", make_tuple("1", "2"));

        Result expectedResult = Result("FOLLOWS", "1", vector<string> {"2"});
        Result result = pkb.getDesignAbstraction("FOLLOWS", "1");

        REQUIRE(expectedResult.areEqual(result));

        pkb.clearAllDatabases(accessKey);

        Result resultAfterClearing = pkb.getDesignAbstraction("FOLLOWS", "1");

        REQUIRE(resultAfterClearing.getQueryEntityName() == "none");
    }

    SECTION("Testing Assign Pattern Database") {
        string accessKey = "CalledForTestingPurposes";

        PKB pkb = PKB();
        pkb.addAssignPattern("a", "a + b", "1");

        string result = pkb.getRightHandExpressionOfAVariableOnAParticularLineNumber("a", "1");

        REQUIRE(result.compare("a + b") == 0);

        pkb.clearAllDatabases(accessKey);

        string resultAfterClearing = pkb.getRightHandExpressionOfAVariableOnAParticularLineNumber("a", "1");

        REQUIRE(resultAfterClearing.empty());
    }

    SECTION("Testing If Pattern Database") {
        string accessKey = "CalledForTestingPurposes";

        PKB pkb = PKB();
        pkb.addPattern("IF", "1", "a");

        unordered_set<string> result = pkb.getAllVariablesUsedInPattern("IF", "1");

        REQUIRE((result.find("a") != result.end()));

        pkb.clearAllDatabases(accessKey);

        unordered_set<string> resultAfterClearing = pkb.getAllVariablesUsedInPattern("IF", "1");

        REQUIRE(resultAfterClearing.empty());
    }

    SECTION("Testing While Pattern Database") {
        string accessKey = "CalledForTestingPurposes";

        PKB pkb = PKB();
        pkb.addPattern("WHILE", "1", "a");

        unordered_set<string> result = pkb.getAllVariablesUsedInPattern("WHILE", "1");

        REQUIRE((result.find("a") != result.end()));

        pkb.clearAllDatabases(accessKey);

        unordered_set<string> resultAfterClearing = pkb.getAllVariablesUsedInPattern("WHILE", "1");

        REQUIRE(resultAfterClearing.empty());
    }

    SECTION("Testing Control Flow Graph Database") {
        string accessKey = "CalledForTestingPurposes";

        PKB pkb = PKB();
        pkb.addControlFlowGraph("Test",
                                vector<int> {1},
                                map<int, vector<int>> {make_pair(1, vector<int> {1})},
                                map<int, int> {make_pair(1, 1)},
                                map<int, vector<int>> {make_pair(1, vector<int> {1})},
                                unordered_set<int> {1});

        vector<int> topologicallySortedElements = pkb.getTopologicallySortedElementsDatabase("Test");
        map<int, vector<int>> blockToStatementNumberElements = pkb.getBlockToStatementNumbersDatabase("Test");
        map<int, int> statementNumberToBlockElements = pkb.getStatementNumberToBlockDatabase("Test");
        map<int, vector<int>> blockToBlockElements = pkb.getBlockToBlockDatabase("Test");
        unordered_set<int> blocksWithBackPointersElements = pkb.getBlocksWithBackPointersDatabase("Test");

        REQUIRE(topologicallySortedElements.size() == 1);
        REQUIRE(blockToStatementNumberElements.size() == 1);
        REQUIRE(statementNumberToBlockElements.size() == 1);
        REQUIRE(blockToBlockElements.size() == 1);
        REQUIRE(blocksWithBackPointersElements.size() == 1);

        pkb.clearAllDatabases(accessKey);

        vector<int> topologicallySortedElementsAfterClearing = pkb.getTopologicallySortedElementsDatabase("Test");
        map<int, vector<int>> blockToStatementNumberElementsAfterClearing = pkb.getBlockToStatementNumbersDatabase("Test");
        map<int, int> statementNumberToBlockElementsAfterClearing = pkb.getStatementNumberToBlockDatabase("Test");
        map<int, vector<int>> blockToBlockElementsAfterClearing = pkb.getBlockToBlockDatabase("Test");
        unordered_set<int> blocksWithBackPointersElementsAfterClearing = pkb.getBlocksWithBackPointersDatabase("Test");

        REQUIRE(topologicallySortedElementsAfterClearing.size() == 1);
        REQUIRE(blockToStatementNumberElementsAfterClearing.size() == 1);
        REQUIRE(statementNumberToBlockElementsAfterClearing.size() == 1);
        REQUIRE(blockToBlockElementsAfterClearing.size() == 1);
        REQUIRE(blocksWithBackPointersElementsAfterClearing.size() == 1);
    }
}

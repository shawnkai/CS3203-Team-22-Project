//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of WhileStatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws1"));

        Result expectedResult("MODIFIES:WHILE", "mws1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent WhileStatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mws2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent WhileStatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an WhileStatementModifies Design Abstraction When Multiple WhileStatementModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mws4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an WhileStatementModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mws6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mws6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mws6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mws6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mws6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mws6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mws6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an WhileStatementModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mws8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mws7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The WhileStatementModifies Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws9", "mws10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws9", "mws10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws9", "mws11"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws9", "mws12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mws9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "MODIFIES:WHILE: mws9: mws10, mws11, mws12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

TEST_CASE("Test 9: Retrieval of All WhileStatementModifies Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws13", "mws14"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws15", "mws16"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws17", "mws18"));

        vector<Result> result = pkbTest.getAllDesignAbstractions("MODIFIES", "WHILE");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 10: Retrieval of Variables Captured By WhileStatementModifies Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();

        pkbTest.clearAllDatabases();

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws19", "mws20"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws21", "mws22"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mws23", "mws24"));

        unordered_map<string, unordered_set<string>> result =
                pkbTest.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "WHILE");

        REQUIRE(result.size() == 3);
    }
}

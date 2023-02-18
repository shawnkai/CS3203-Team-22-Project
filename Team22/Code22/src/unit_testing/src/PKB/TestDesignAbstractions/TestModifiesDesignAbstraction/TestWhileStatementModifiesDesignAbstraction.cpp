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
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mis1"));

        Result expectedResult("MODIFIES:WHILE", "mis1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent WhileStatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mis2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mis2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent WhileStatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mis0"));

        REQUIRE(pkbResult.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of an WhileStatementModifies Design Abstraction When Multiple WhileStatementModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mis4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mis4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an WhileStatementModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mis6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mis6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an WhileStatementModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mis8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("WHILE", "mis7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:WHILE: mis7: 1, 2, ");
    }
}

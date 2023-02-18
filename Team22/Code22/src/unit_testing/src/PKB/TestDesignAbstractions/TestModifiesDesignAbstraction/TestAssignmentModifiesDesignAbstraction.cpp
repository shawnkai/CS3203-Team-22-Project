//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of AssignmentModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma1"));

        Result expectedResult("MODIFIES:ASSIGNMENT", "ma1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent AssignmentModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent AssignmentModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma0"));

        REQUIRE(pkbResult.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of an AssignmentModifies Design Abstraction When Multiple AssignmentModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an AssignmentModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "ma6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "ma6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "ma6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ma6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "ma6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "ma6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an AssignmentModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "ma8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma7: 1, 2, ");
    }
}

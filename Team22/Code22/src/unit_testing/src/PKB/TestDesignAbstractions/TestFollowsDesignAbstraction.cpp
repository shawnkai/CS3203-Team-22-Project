//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of Follows Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a1", "a2"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWS", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }
}

TEST_CASE("Test 2: Retrieval of Follows Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a3", "a4"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWS", make_pair("_", "a3"));

        REQUIRE(result.toString() == "FOLLOWS: a3: a4, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent Follows Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a5", "a6"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWS", make_pair("_", "a0"));

        REQUIRE(result.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of a Follows Design Abstraction When Multiple Follows Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a7", "a8"));
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a9", "a10"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWS", make_pair("_", "a7"));

        REQUIRE(result.getQueryResult()[0] == "a8");
    }
}

TEST_CASE("Test 5: Retrieval of an Follows Design Abstraction When Multiple Same Follows Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a11", "a13"));

        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a11", "a13"));
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a12", "a13"));
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a11", "a14"));

        Result pkbResult = pkbTest.getDesignAbstraction("FOLLOWS", make_pair("_", "a11"));

        REQUIRE(pkbResult.toString() == "FOLLOWS: a11: a13, a14, ");
    }
}

TEST_CASE("Test 6: Populate The Follows Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a15", "a16"));
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a15", "a16"));
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a15", "a17"));
        pkbTest.addDesignAbstraction("FOLLOWS", make_tuple("_", "a15", "a18"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("FOLLOWS", make_pair("_", "a15"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("FOLLOWS", make_pair("_", "a15"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "FOLLOWS: a15: a16, a17, a18, ")
        && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

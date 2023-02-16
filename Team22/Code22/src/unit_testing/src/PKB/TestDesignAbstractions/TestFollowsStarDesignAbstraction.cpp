//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of FollowsStar Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "a1", "a2"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWSSTAR", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }
}

TEST_CASE("Test 2: Retrieval of FollowsStar Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "a3", "a4"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWSSTAR", make_pair("_", "a3"));

        REQUIRE(result.toString() == "FOLLOWSSTAR: a3: a4, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent FollowsStar Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "a5", "a6"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWSSTAR", make_pair("_", "a0"));

        REQUIRE(result.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of a FollowsStar Abstraction When Multiple Follows Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "a7", "a8"));
        pkbTest.addDesignAbstraction("FOLLOWSSTAR", make_tuple("_", "a9", "a10"));

        Result result = pkbTest.getDesignAbstraction("FOLLOWSSTAR", make_pair("_", "a7"));

        REQUIRE(result.getQueryResult()[0] == "a8");
    }
}

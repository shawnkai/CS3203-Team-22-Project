//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of Parent Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a1", "a2"));

        Result result = pkbTest.getDesignAbstraction("PARENT", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }
}

TEST_CASE("Test 2: Retrieval of Parent Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a3", "a4"));

        Result result = pkbTest.getDesignAbstraction("PARENT", make_pair("_", "a3"));

        REQUIRE(result.toString() == "PARENT: a3: a4, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent Parent Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a5", "a6"));

        Result result = pkbTest.getDesignAbstraction("PARENT", make_pair("_", "a0"));

        REQUIRE(result.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of a Parent Design Abstraction When Multiple Parent Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a7", "a8"));
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a9", "a10"));

        Result result = pkbTest.getDesignAbstraction("PARENT", make_pair("_", "a7"));

        REQUIRE(result.getQueryResult()[0] == "a8");
    }
}

TEST_CASE("Test 5: Retrieval of an Parent Design Abstraction When Multiple Same Parent Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a11", "a13"));

        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a11", "a13"));
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a12", "a13"));
        pkbTest.addDesignAbstraction("PARENT", make_tuple("_", "a11", "a14"));

        Result pkbResult = pkbTest.getDesignAbstraction("PARENT", make_pair("_", "a11"));

        REQUIRE(pkbResult.toString() == "PARENT: a11: a13, a14, ");
    }
}

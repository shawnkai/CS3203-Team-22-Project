//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of ReadStatement Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("READ", "r1");

        Result expectedResult("READ", "r1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: ReadStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("READ", "r2");

        Result expectedResult("READ", "r2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: ReadStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("READ", "r3");

        Result expectedResult("READ", "r3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: ReadStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("READ", "r0");

        Result expectedResult("READ", "r4", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: ReadStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "r5");

        Result expectedResult("READ", "r5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: ReadStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "r0");

        Result expectedResult("READ", "r6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: ReadStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "r0");

        Result expectedResult("READ", "r7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: ReadStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "r8");

        Result expectedResult("READ", "r8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: ReadStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("READ", make_tuple("r9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("READ", "r0");

        Result expectedResult("READ", "r9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

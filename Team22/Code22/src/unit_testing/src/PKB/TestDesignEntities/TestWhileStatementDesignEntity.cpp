//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of WhileStatement Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("WHILE", "ws1");

        Result expectedResult("WHILE", "ws1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: WhileStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("WHILE", "ws2");

        Result expectedResult("WHILE", "ws2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: WhileStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("WHILE", "ws3");

        Result expectedResult("WHILE", "ws3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: WhileStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("WHILE", "ws0");

        Result expectedResult("WHILE", "ws4", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: WhileStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ws5");

        Result expectedResult("WHILE", "ws5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: WhileStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ws0");

        Result expectedResult("WHILE", "ws6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: WhileStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ws0");

        Result expectedResult("WHILE", "ws7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: WhileStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ws8");

        Result expectedResult("WHILE", "ws8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: WhileStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("WHILE", make_tuple("ws9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("WHILE", "ws0");

        Result expectedResult("WHILE", "ws9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

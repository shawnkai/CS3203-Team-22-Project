//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of AssignStatement Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGN", "as1");

        Result expectedResult("ASSIGN", "as1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: AssignStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGN", "as2");

        Result expectedResult("ASSIGN", "as2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: AssignStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGN", "as3");

        Result expectedResult("ASSIGN", "as3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: AssignStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGN", "as0");

        Result expectedResult("ASSIGN", "as4", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: AssignStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as5");

        Result expectedResult("ASSIGN", "as5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: AssignStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as0");

        Result expectedResult("ASSIGN", "as6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: AssignStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as0");

        Result expectedResult("ASSIGN", "as7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: AssignStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as8");

        Result expectedResult("ASSIGN", "as8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: AssignStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGN", make_tuple("as9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGN", "as0");

        Result expectedResult("ASSIGN", "as9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}
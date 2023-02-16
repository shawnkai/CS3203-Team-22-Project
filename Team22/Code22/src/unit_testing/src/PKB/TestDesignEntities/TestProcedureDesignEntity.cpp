//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of Procedure Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "p1");

        Result expectedResult("PROCEDURE", "p1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Procedure Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "p2");

        Result expectedResult("PROCEDURE", "p2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: Procedure Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "p3");

        Result expectedResult("PROCEDURE", "p3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: Procedure Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "p4");

        Result expectedResult("PROCEDURE", "p0", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: Procedure Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "p5");

        Result expectedResult("PROCEDURE", "p5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: Procedure Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "p0");

        Result expectedResult("PROCEDURE", "p6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Procedure Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "p0");

        Result expectedResult("PROCEDURE", "p7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Procedure Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "p8");

        Result expectedResult("PROCEDURE", "p8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: Procedure Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PROCEDURE", make_tuple("p9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "p0");

        Result expectedResult("PROCEDURE", "p9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

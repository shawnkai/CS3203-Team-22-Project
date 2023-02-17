//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of Variable Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "v1");

        Result expectedResult("VARIABLE", "v1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Variable Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "v2");

        Result expectedResult("VARIABLE", "v2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: Variable Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "v3");

        Result expectedResult("VARIABLE", "v3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: Variable Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "v0");

        Result expectedResult("VARIABLE", "v4", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: Variable Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "v5");

        Result expectedResult("VARIABLE", "v5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: Variable Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "v0");

        Result expectedResult("VARIABLE", "v6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Variable Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "v0");

        Result expectedResult("VARIABLE", "v7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: Variable Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PROCEDURE", "v8");

        Result expectedResult("VARIABLE", "v8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: Variable Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "v0");

        Result expectedResult("VARIABLE", "v9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: Variable Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v10", "1"));
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v10", "1"));
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v10", "2"));
        pkbTest.addDesignEntity("VARIABLE", make_tuple("v11", "3"));

        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "v10");

        Result expectedResult("VARIABLE", "v10", vector<string>{"1", "2"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

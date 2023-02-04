//
// Created by Jai Lulla  on 3/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Trial PKB Test") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("variable", make_tuple("a", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "a");

        Result expectedResult("VARIABLE", "a", vector<string> {"1"});

//    REQUIRE(pkbTest.addDesignEntity("variable", make_tuple("a", "1")))
//    REQUIRE(1==1);
        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

// Need to section below, as some code is being carried forward unintentionally
TEST_CASE("PKB Test 1: Same Type, Same Variable Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest1 = PKB();
        pkbTest1.addDesignEntity("variable", make_tuple("a", "1"));
        Result pkbResult1 = pkbTest1.getDesignEntity("VARIABLE", "a");

        Result expectedResult1("VARIABLE", "a", vector<string>{"1"});

        REQUIRE(pkbResult1.areEqual(expectedResult1));
    }
}

TEST_CASE("PKB Test 2: Same Type, Different Variable Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest2 = PKB();
        pkbTest2.addDesignEntity("variable", make_tuple("b", "1"));
        Result pkbResult2 = pkbTest2.getDesignEntity("VARIABLE", "a");

        Result expectedResult2("VARIABLE", "a", vector<string>{"1"});

        REQUIRE(!pkbResult2.areEqual(expectedResult2));
    }
}

TEST_CASE("PKB Test 3: Same Type, Different Variable Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest3 = PKB();
        pkbTest3.addDesignEntity("variable", make_tuple("b", "2"));
        Result pkbResult3 = pkbTest3.getDesignEntity("VARIABLE", "a");

        Result expectedResult3("VARIABLE", "a", vector<string>{"1"});

        REQUIRE(!pkbResult3.areEqual(expectedResult3));
    }
}

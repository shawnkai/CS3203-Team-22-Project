//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of Statement Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("STATEMENT", "s1");

        Result expectedResult("STATEMENT", "s1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Statement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("STATEMENT", "s2");

        Result expectedResult("STATEMENT", "s2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: Statement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("STATEMENT", "s3");

        Result expectedResult("STATEMENT", "s3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: Statement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("STATEMENT", "s0");

        Result expectedResult("STATEMENT", "s4", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: Statement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "s5");

        Result expectedResult("STATEMENT", "s5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: Statement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "s0");

        Result expectedResult("STATEMENT", "s6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Statement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "s0");

        Result expectedResult("STATEMENT", "s7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: Statement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "s8");

        Result expectedResult("STATEMENT", "s8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: Statement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("STATEMENT", "s0");

        Result expectedResult("STATEMENT", "s9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: Statement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s10", "1"));
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s10", "1"));
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s10", "2"));
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s11", "3"));

        Result pkbResult = pkbTest.getDesignEntity("STATEMENT", "s10");

        Result expectedResult("STATEMENT", "s10", vector<string>{"1", "2"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: Statement Design Entity, Populate The Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s12", "1"));
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s12", "1"));
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s12", "2"));
        pkbTest.addDesignEntity("STATEMENT", make_tuple("s12", "3"));

        Result pkbResultBeforeClearing = pkbTest.getDesignEntity("STATEMENT", "s12");

        Result expectedResultBeforeClearing("STATEMENT", "s12", vector<string>{"1", "2", "3"});

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignEntity("STATEMENT", "s12");

        Result expectedResultAfterClearing("none", "none", vector<string>{"none"});

        REQUIRE(((pkbResultBeforeClearing.areEqual(expectedResultBeforeClearing))
                 && (pkbResultAfterClearing.areEqual(expectedResultAfterClearing))));
    }
}

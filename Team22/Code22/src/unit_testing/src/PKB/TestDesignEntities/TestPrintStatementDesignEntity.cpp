//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of PrintStatement Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PRINT", "ps1");

        Result expectedResult("PRINT", "ps1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: PrintStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PRINT", "ps2");

        Result expectedResult("PRINT", "ps2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: PrintStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PRINT", "ps3");

        Result expectedResult("PRINT", "ps3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: PrintStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PRINT", "ps0");

        Result expectedResult("PRINT", "ps4", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: PrintStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ps5");

        Result expectedResult("PRINT", "ps5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: PrintStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ps0");

        Result expectedResult("PRINT", "ps6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: PrintStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ps0");

        Result expectedResult("PRINT", "ps7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: PrintStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "ps8");

        Result expectedResult("PRINT", "ps8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: PrintStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("PRINT", "ps0");

        Result expectedResult("PRINT", "ps9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: PrintStatement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps10", "1"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps10", "1"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps10", "2"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps11", "3"));

        Result pkbResult = pkbTest.getDesignEntity("PRINT", "ps10");

        Result expectedResult("PRINT", "ps10", vector<string>{"1", "2"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: PrintStatement Design Entity, Populate The Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "1"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "1"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "2"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "3"));

        Result pkbResultBeforeClearing = pkbTest.getDesignEntity("PRINT", "ps12");

        Result expectedResultBeforeClearing("PRINT", "ps12", vector<string>{"1", "2", "3"});

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignEntity("PRINT", "ps12");

        Result expectedResultAfterClearing("none", "none", vector<string>{"none"});

        REQUIRE(((pkbResultBeforeClearing.areEqual(expectedResultBeforeClearing))
                 && (pkbResultAfterClearing.areEqual(expectedResultAfterClearing))));
    }
}

TEST_CASE("Test 12: PrintStatement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "1"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "1"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "2"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps12", "3"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps13", "1"));
        pkbTest.addDesignEntity("PRINT", make_tuple("ps14", "1"));

        int countBeforeClearing = pkbTest.getNumberOfDesignEntity("PRINT");

        pkbTest.clearAllDatabases();

        int countAfterClearing = pkbTest.getNumberOfDesignEntity("PRINT");

        REQUIRE(((countAfterClearing == 0) && (countBeforeClearing == 3)));
    }
}

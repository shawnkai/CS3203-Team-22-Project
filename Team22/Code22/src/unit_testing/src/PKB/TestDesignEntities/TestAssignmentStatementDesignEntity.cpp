//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of AssignmentStatement Design Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as1", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGNMENT", "as1");

        Result expectedResult("ASSIGNMENT", "as1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: AssignmentStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as2", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGNMENT", "as2");

        Result expectedResult("ASSIGNMENT", "as2", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: AssignmentStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as3", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGNMENT", "as3");

        Result expectedResult("ASSIGNMENT", "as3", vector<string>{"2"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: AssignmentStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as4", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGNMENT", "as0");

        Result expectedResult("ASSIGNMENT", "as4", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: AssignmentStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as5", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as5");

        Result expectedResult("ASSIGNMENT", "as5", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: AssignmentStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as6", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as0");

        Result expectedResult("ASSIGNMENT", "as6", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: AssignmentStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as7", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as0");

        Result expectedResult("ASSIGNMENT", "as7", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: AssignmentStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as8", "1"));
        Result pkbResult = pkbTest.getDesignEntity("VARIABLE", "as8");

        Result expectedResult("ASSIGNMENT", "as8", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: AssignmentStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as9", "1"));
        Result pkbResult = pkbTest.getDesignEntity("ASSIGNMENT", "as0");

        Result expectedResult("ASSIGNMENT", "as9", vector<string>{"1"});

        REQUIRE(!pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: AssignmentStatement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as10", "1"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as10", "1"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as10", "2"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as11", "3"));

        Result pkbResult = pkbTest.getDesignEntity("ASSIGNMENT", "as10");

        Result expectedResult("ASSIGNMENT", "as10", vector<string>{"1", "2"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: AssignmentStatement Design Entity, Populate The Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "1"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "1"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "2"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "3"));

        Result pkbResultBeforeClearing = pkbTest.getDesignEntity("ASSIGNMENT", "as12");

        Result expectedResultBeforeClearing("ASSIGNMENT", "as12", vector<string>{"1", "2", "3"});

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignEntity("ASSIGNMENT", "as12");

        Result expectedResultAfterClearing("none", "none", vector<string>{"none"});

        REQUIRE(((pkbResultBeforeClearing.areEqual(expectedResultBeforeClearing))
        && (pkbResultAfterClearing.areEqual(expectedResultAfterClearing))));
    }
}

TEST_CASE("Test 12: AssignmentStatement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "1"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "1"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "2"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as12", "3"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as13", "1"));
        pkbTest.addDesignEntity("ASSIGNMENT", make_tuple("as14", "1"));

        int countBeforeClearing = pkbTest.getNumberOfDesignEntity("ASSIGNMENT");

        pkbTest.clearAllDatabases();

        int countAfterClearing = pkbTest.getNumberOfDesignEntity("ASSIGNMENT");

        REQUIRE(((countAfterClearing == 0) && (countBeforeClearing == 3)));
    }
}

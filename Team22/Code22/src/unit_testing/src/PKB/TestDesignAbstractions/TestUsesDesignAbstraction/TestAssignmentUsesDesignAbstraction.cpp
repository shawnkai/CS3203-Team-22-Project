//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of AssignmentUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua1"));

        Result expectedResult("USES:ASSIGNMENT", "ua1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent AssignmentUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua2"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent AssignmentUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an AssignmentUses Design Abstraction When Multiple AssignmentUses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua4", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua4"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an AssignmentUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua6", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "ua6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "ua6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "ua6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "ua6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "ua6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "ua6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua6"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an AssignmentUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua7", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua7", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua7", "2"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "ua8", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua7"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The AssignmentUses Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua9", "ua10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua9", "ua10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua9", "ua11"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua9", "ua12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "USES:ASSIGNMENT: ua9: ua10, ua11, ua12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of StatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms1"));

        Result expectedResult("MODIFIES:STATEMENT", "ms1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent StatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent StatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms0"));

        REQUIRE(pkbResult.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of an StatementModifies Design Abstraction When Multiple StatementModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an StatementModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "ms6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "ms6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ms6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "ms6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "ms6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "ms6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an StatementModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ms8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The StatementModifies Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms9", "ms10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms9", "ms10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms9", "ms11"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms9", "ms12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "MODIFIES:STATEMENT: ms9: ms10, ms11, ms12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: None, ")));
    }
}

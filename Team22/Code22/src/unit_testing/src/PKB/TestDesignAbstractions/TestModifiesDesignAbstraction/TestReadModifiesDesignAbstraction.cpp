//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of ReadModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr1"));

        Result expectedResult("MODIFIES:READ", "mr1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent ReadModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ReadModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ReadModifies Design Abstraction When Multiple ReadModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ReadModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mr6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mr6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mr6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mr6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mr6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mr6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ReadModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mr8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The ReadModifies Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr9", "mr10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr9", "mr10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr9", "mr11"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr9", "mr12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "MODIFIES:READ: mr9: mr10, mr11, mr12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

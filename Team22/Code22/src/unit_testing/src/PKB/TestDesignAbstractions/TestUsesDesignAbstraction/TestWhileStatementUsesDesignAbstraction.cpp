//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of WhileStatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws1"));

        Result expectedResult("USES:WHILE", "uws1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent WhileStatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws2"));

        REQUIRE(pkbResult.toString() == "USES:WHILE: uws2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent WhileStatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an WhileStatementUses Design Abstraction When Multiple WhileStatementUses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws4", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws4"));

        REQUIRE(pkbResult.toString() == "USES:WHILE: uws4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an WhileStatementUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws6", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "uws6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "uws6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "uws6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "uws6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "uws6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uws6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws6"));

        REQUIRE(pkbResult.toString() == "USES:WHILE: uws6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an WhileStatementUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws7", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws7", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws7", "2"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "uws8", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws7"));

        REQUIRE(pkbResult.toString() == "USES:WHILE: uws7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The WhileStatementUses Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws9", "uws10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws9", "uws10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws9", "uws11"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uws9", "uws12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("USES", make_pair("WHILE", "uws9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "USES:WHILE: uws9: uws10, uws11, uws12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

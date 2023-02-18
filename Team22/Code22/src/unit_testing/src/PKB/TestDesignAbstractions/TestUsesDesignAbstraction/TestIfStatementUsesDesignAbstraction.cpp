//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of IfStatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("IF", "uis1"));

        Result expectedResult("USES:IF", "uis1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent IfStatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("IF", "uis2"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent IfStatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("IF", "uis0"));

        REQUIRE(pkbResult.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of an IfStatementUses Design Abstraction When Multiple IfStatementUses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis4", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("IF", "uis4"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an IfStatementUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis6", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "uis6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "uis6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "uis6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "uis6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "uis6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "uis6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("IF", "uis6"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an IfStatementUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis7", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis7", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis7", "2"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "uis8", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "uis8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("IF", "uis7"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis7: 1, 2, ");
    }
}

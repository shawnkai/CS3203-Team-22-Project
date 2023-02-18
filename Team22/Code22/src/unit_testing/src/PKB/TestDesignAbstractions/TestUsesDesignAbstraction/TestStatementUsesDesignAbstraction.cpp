//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of StatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us1"));

        Result expectedResult("USES:STATEMENT", "us1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent StatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us2"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent StatementUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us0"));

        REQUIRE(pkbResult.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of an StatementUses Design Abstraction When Multiple StatementUses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us4", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us4"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an StatementUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us6", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "us6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "us6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "us6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "us6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "us6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "us6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us6"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an StatementUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us7", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us7", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us7", "2"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us8", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us7"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us7: 1, 2, ");
    }
}

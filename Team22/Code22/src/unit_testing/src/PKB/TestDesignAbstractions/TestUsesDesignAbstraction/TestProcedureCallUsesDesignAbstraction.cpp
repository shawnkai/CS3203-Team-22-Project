//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of ProcedureCallUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc1"));

        Result expectedResult("USES:PROCEDURECALL", "updc1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent ProcedureCallUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc2"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ProcedureCallUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc0"));

        REQUIRE(pkbResult.toString() == "none: none: None, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ProcedureCallUses Design Abstraction When Multiple ProcedureCallUses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc4", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc4"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ProcedureCallUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc6", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "updc6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "updc6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "updc6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "updc6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc6"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ProcedureCallUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc7", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc7", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc7", "2"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "updc8", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc7"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc7: 1, 2, ");
    }
}

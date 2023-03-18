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

        REQUIRE(pkbResult.toString() == "none: none: none, ");
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
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "updc6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "updc6", "1"));

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

TEST_CASE("Test 7: Populate The ProcedureCallUses Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc9", "updc10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc9", "updc10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc9", "updc11"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc9", "updc12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "USES:PROCEDURECALL: updc9: updc10, updc11, updc12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

TEST_CASE("Test 9: Retrieval of All ProcedureCallUses Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc13", "updc14"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc15", "updc16"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc17", "updc18"));

        vector<Result> result = pkbTest.getAllDesignAbstractions("USES", "PROCEDURECALL");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 10: Retrieval of Variables Captured By ProcedureCallUses Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();

        pkbTest.clearAllDatabases();

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc19", "updc20"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc21", "updc22"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc23", "updc24"));

        unordered_map<string, unordered_set<string>> result =
                pkbTest.getAllVariablesCapturedByDesignAbstraction("USES", "PROCEDURECALL");

        REQUIRE(result.size() == 3);
    }
}

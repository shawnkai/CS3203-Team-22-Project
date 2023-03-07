//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of ProcedureUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd1"));

        Result expectedResult("USES:PROCEDURE", "upd1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent ProcedureUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd2"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ProcedureUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ProcedureUses Design Abstraction When Multiple ProcedureUses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd4", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd4"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ProcedureUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd6", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "upd6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "upd6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "upd6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "upd6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "upd6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "upd6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd6"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ProcedureUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd7", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd7", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd7", "2"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "upd8", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd7"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The ProcedureUses Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd9", "upd10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd9", "upd10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd9", "upd11"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd9", "upd12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "USES:PROCEDURE: upd9: upd10, upd11, upd12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

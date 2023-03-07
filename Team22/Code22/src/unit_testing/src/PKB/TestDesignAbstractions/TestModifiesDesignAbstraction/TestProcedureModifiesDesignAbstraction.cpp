//
// Created by Jai Lulla  on 17/2/23.
//


#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of ProcedureModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp1"));

        Result expectedResult("MODIFIES:PROCEDURE", "mp1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Retrieval of an existent ProcedureModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURE: mp2: 1, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ProcedureModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ProcedureModifies Design Abstraction When Multiple ProcedureModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURE: mp4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ProcedureModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mp6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mp6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mp6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mp6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mp6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURE: mp6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ProcedureModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mp8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURE: mp7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The ProcedureModifies Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp9", "mp10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp9", "mp10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp9", "mp11"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mp9", "mp12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURE", "mp9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "MODIFIES:PROCEDURE: mp9: mp10, mp11, mp12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

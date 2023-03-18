//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

TEST_CASE("Test 1: Creation of CallsStar Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a1", "a2"));

        Result result = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }

    SECTION("Using API With A Tuple of Size 2") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("a1", "a2"));

        Result result = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }
}

TEST_CASE("Test 2: Retrieval of CallsStar Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a3", "a4"));

        Result result = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a3"));

        REQUIRE(result.toString() == "CALLSSTAR: a3: a4, ");
    }

    SECTION("Using API Without Tuple") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a3", "a4"));

        Result result = pkbTest.getDesignAbstraction("CALLSSTAR", "a3");

        REQUIRE(result.toString() == "CALLSSTAR: a3: a4, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent CallsStar Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a5", "a6"));

        Result result = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a0"));

        REQUIRE(result.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of a CallsStar Design Abstraction When Multiple CallsStar Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a7", "a8"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a9", "a10"));

        Result result = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a7"));

        REQUIRE(result.getQueryResult()[0] == "a8");
    }
}

TEST_CASE("Test 5: Retrieval of an CallsStar Design Abstraction When Multiple Same CallsStar Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a11", "a13"));

        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a11", "a13"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a12", "a13"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a11", "a14"));

        Result pkbResult = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a11"));

        REQUIRE(pkbResult.toString() == "CALLSSTAR: a11: a13, a14, ");
    }
}

TEST_CASE("Test 6: Populate The CallsStar Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a15", "a16"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a15", "a16"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a15", "a17"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a15", "a18"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a15"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a15"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "CALLSSTAR: a15: a16, a17, a18, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

TEST_CASE("Test 7: Retrieval of All CallsStar Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a19", "a20"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a21", "a22"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a23", "a24"));

        vector<Result> result = pkbTest.getAllDesignAbstractions("CALLSSTAR", "_");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By CallsStar Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();

        pkbTest.clearAllDatabases();

        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a25", "a26"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a27", "a28"));
        pkbTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a29", "a30"));

        unordered_map<string, unordered_set<string>> result =
                pkbTest.getAllVariablesCapturedByDesignAbstraction("CALLSSTAR", "_");

        REQUIRE(result.size() == 3);
    }
}

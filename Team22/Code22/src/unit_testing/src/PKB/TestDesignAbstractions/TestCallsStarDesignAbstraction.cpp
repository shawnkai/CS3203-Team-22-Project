//
// Created by Jai Lulla  on 8/3/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsInterface.h"

using namespace std;

TEST_CASE("Test 1: Creation of CallsStar Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a1", "a2"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }

    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("a1", "a2"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }
}

TEST_CASE("Test 2: Retrieval of CallsStar Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a3", "a4"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a3"));

        REQUIRE(result.toString() == "CALLSSTAR: a3: a4, ");
    }

    SECTION("Using API Without Tuple") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a3", "a4"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLSSTAR", "a3");

        REQUIRE(result.toString() == "CALLSSTAR: a3: a4, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent CallsStar Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a5", "a6"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a0"));

        REQUIRE(result.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of a CallsStar Design Abstraction When Multiple CallsStar Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a7", "a8"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a9", "a10"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a7"));

        REQUIRE(result.getQueryResult()[0] == "a8");
    }
}

TEST_CASE("Test 5: Retrieval of an CallsStar Design Abstraction When Multiple Same CallsStar Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a11", "a13"));

        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a11", "a13"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a12", "a13"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a11", "a14"));

        Result DesignAbstractionsControllerResult = designAbstractionsControllerTest.getDesignAbstraction("CALLSSTAR", make_pair("_", "a11"));

        REQUIRE(DesignAbstractionsControllerResult.toString() == "CALLSSTAR: a11: a13, a14, ");
    }
}

TEST_CASE("Test 6: Retrieval of All CallsStar Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a19", "a20"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a21", "a22"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a23", "a24"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("CALLSSTAR", "_");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 7: Retrieval of Variables Captured By CallsStar Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a25", "a26"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a27", "a28"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLSSTAR", make_tuple("_", "a29", "a30"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("CALLSSTAR", "_");

        REQUIRE(
                ((result.find("a26") != result.end()) &&
                 (result.find("a28") != result.end()) &&
                 (result.find("a30") != result.end()))
        );
    }
}

//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsInterface.h"

using namespace std;

TEST_CASE("Test 1: Creation of Calls Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a1", "a2"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLS", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }

    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("a1", "a2"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLS", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }
}

TEST_CASE("Test 2: Retrieval of Calls Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a3", "a4"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLS", make_pair("_", "a3"));

        REQUIRE(result.toString() == "CALLS: a3: a4, ");
    }

    SECTION("Using API Without Tuple") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a3", "a4"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLS", "a3");

        REQUIRE(result.toString() == "CALLS: a3: a4, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent Calls Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a5", "a6"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLS", make_pair("_", "a0"));

        REQUIRE(result.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of a Calls Design Abstraction When Multiple Calls Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a7", "a8"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a9", "a10"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("CALLS", make_pair("_", "a7"));

        REQUIRE(result.getQueryResult()[0] == "a8");
    }
}

TEST_CASE("Test 5: Retrieval of an Calls Design Abstraction When Multiple Same Calls Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a11", "a13"));

        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a11", "a13"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a12", "a13"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a11", "a14"));

        Result DesignAbstractionsControllerResult = designAbstractionsControllerTest.getDesignAbstraction("CALLS", make_pair("_", "a11"));

        REQUIRE(DesignAbstractionsControllerResult.toString() == "CALLS: a11: a13, a14, ");
    }
}

TEST_CASE("Test 6: Retrieval of All Calls Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a19", "a20"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a21", "a22"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a23", "a24"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("CALLS", "_");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 7: Retrieval of Variables Captured By Calls Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a25", "a26"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a27", "a28"));
        designAbstractionsControllerTest.addDesignAbstraction("CALLS", make_tuple("_", "a29", "a30"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("CALLS", "_");

        REQUIRE(
                ((result.find("a26") != result.end()) &&
                 (result.find("a28") != result.end()) &&
                 (result.find("a30") != result.end()))
        );
    }
}

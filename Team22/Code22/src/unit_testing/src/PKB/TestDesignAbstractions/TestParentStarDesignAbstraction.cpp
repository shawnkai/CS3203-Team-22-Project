//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsController.h"

using namespace std;

TEST_CASE("Test 1: Creation of ParentStar Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a1", "a2"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("PARENTSTAR", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }

    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("a1", "a2"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("PARENTSTAR", make_pair("_", "a1"));

        REQUIRE(((result.getQueryEntityName() == "a1") && (result.getQueryResult().size() != 0)));
    }
}

TEST_CASE("Test 2: Retrieval of ParentStar Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a3", "a4"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("PARENTSTAR", make_pair("_", "a3"));

        REQUIRE(result.toString() == "PARENTSTAR: a3: a4, ");
    }

    SECTION("Using API Without Tuple") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a3", "a4"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("PARENTSTAR", "a3");

        REQUIRE(result.toString() == "PARENTSTAR: a3: a4, ");
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ParentStar Design Abstraction") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a5", "a6"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("PARENTSTAR", make_pair("_", "a0"));

        REQUIRE(result.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of a ParentStar Design Abstraction When Multiple ParentStar Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a7", "a8"));
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a9", "a10"));

        Result result = designAbstractionsControllerTest.getDesignAbstraction("PARENTSTAR", make_pair("_", "a7"));

        REQUIRE(result.getQueryResult()[0] == "a8");
    }
}

TEST_CASE("Test 5: Retrieval of an ParentStar Design Abstraction When Multiple Same ParentStar Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a11", "a13"));

        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a11", "a13"));
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a12", "a13"));
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a11", "a14"));

        Result DesignAbstractionsControllerResult = designAbstractionsControllerTest.getDesignAbstraction("PARENTSTAR", make_pair("_", "a11"));

        REQUIRE(DesignAbstractionsControllerResult.toString() == "PARENTSTAR: a11: a13, a14, ");
    }
}

TEST_CASE("Test 6: Retrieval of All ParentStar Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a19", "a20"));
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a21", "a22"));
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a23", "a24"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("PARENTSTAR", "_");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 7: Retrieval of Variables Captured By ParentStar Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a25", "a26"));
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a27", "a28"));
        designAbstractionsControllerTest.addDesignAbstraction("PARENTSTAR", make_tuple("_", "a29", "a30"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("PARENTSTAR", "_");

        REQUIRE(result.size() == 3);
    }
}

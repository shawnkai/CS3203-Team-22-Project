//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "PKB/Interfaces/DesignAbstractionsInterface.h"
#include "catch.hpp"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of ReadModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr1"));

        Result expectedResult("MODIFIES:READ", "mr1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("mr1", "1"));
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent ReadModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", "mr2");
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ReadModifies Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ReadModifies Design Abstraction When Multiple ReadModifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ReadModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mr6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mr6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mr6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mr6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mr6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mr6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ReadModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mr8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("READ", "mr7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:READ: mr7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All ReadModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr13", "mr14"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr15", "mr16"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr17", "mr18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("MODIFIES", "READ");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By ReadModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr19", "mr20"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr21", "mr22"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mr23", "mr24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "READ");

        REQUIRE(
                ((result.find("mr20") != result.end()) &&
                 (result.find("mr22") != result.end()) &&
                 (result.find("mr24") != result.end())));
    }
}

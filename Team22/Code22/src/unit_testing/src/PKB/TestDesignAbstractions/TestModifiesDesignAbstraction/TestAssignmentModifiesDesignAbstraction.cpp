//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "PKB/Interfaces/DesignAbstractionsInterface.h"
#include "catch.hpp"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of AssignmentModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma1"));

        Result expectedResult("MODIFIES:ASSIGNMENT", "ma1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ma1", "1"));
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent AssignmentModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", "ma2");
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent AssignmentModifies Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an AssignmentModifies Design Abstraction When Multiple AssignmentModifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an AssignmentModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "ma6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "ma6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "ma6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ma6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "ma6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "ma6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an AssignmentModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "ma8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("ASSIGNMENT", "ma7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:ASSIGNMENT: ma7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All AssignmentModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma13", "ma14"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma15", "ma16"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma17", "ma18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("MODIFIES", "ASSIGNMENT");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By AssignmentModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma19", "ma20"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma21", "ma22"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ma23", "ma24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "ASSIGNMENT");

        REQUIRE(
                ((result.find("ma20") != result.end()) &&
                 (result.find("ma22") != result.end()) &&
                 (result.find("ma24") != result.end())));
    }
}

//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsInterface.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of StatementModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms1"));

        Result expectedResult("MODIFIES:STATEMENT", "ms1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ms1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent StatementModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", "ms2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent StatementModifies Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an StatementModifies Design Abstraction When Multiple StatementModifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an StatementModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "ms6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "ms6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ms6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "ms6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "ms6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "ms6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an StatementModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "ms8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("STATEMENT", "ms7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:STATEMENT: ms7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All StatementModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms13", "ms14"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms15", "ms16"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms17", "ms18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("MODIFIES", "STATEMENT");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By StatementModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms19", "ms20"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms21", "ms22"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "ms23", "ms24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "STATEMENT");

        REQUIRE(
                ((result.find("ms20") != result.end()) &&
                 (result.find("ms22") != result.end()) &&
                 (result.find("ms24") != result.end()))
        );
    }
}

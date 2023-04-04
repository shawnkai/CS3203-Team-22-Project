//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsInterface.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of AssignmentUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua1"));

        Result expectedResult("USES:ASSIGNMENT", "ua1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ua1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent AssignmentUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua2"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("USES", "ua2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent AssignmentUses Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an AssignmentUses Design Abstraction When Multiple AssignmentUses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua4"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an AssignmentUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "ua6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "ua6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "ua6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "ua6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("WHILE", "ua6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "ua6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua6"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an AssignmentUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "ua8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("ASSIGNMENT", "ua7"));

        REQUIRE(pkbResult.toString() == "USES:ASSIGNMENT: ua7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All AssignmentUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua13", "ua14"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua15", "ua16"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua17", "ua18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("USES", "ASSIGNMENT");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By AssignmentUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua19", "ua20"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua21", "ua22"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "ua23", "ua24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("USES", "ASSIGNMENT");

        REQUIRE(
                ((result.find("ua20") != result.end()) &&
                 (result.find("ua22") != result.end()) &&
                 (result.find("ua24") != result.end()))
        );
    }
}

//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "PKB/Interfaces/DesignAbstractionsInterface.h"
#include "catch.hpp"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of IfStatementUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("IF", "uis1"));

        Result expectedResult("USES:IF", "uis1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("uis1", "1"));
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent IfStatementUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("IF", "uis2"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("USES", "uis2");
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent IfStatementUses Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("IF", "uis0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an IfStatementUses Design Abstraction When Multiple IfStatementUses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("IF", "uis4"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an IfStatementUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "uis6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "uis6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "uis6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "uis6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "uis6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("WHILE", "uis6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("IF", "uis6"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an IfStatementUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "uis8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("IF", "uis7"));

        REQUIRE(pkbResult.toString() == "USES:IF: uis7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All IfStatementUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis13", "uis14"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis15", "uis16"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis17", "uis18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("USES", "IF");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By IfStatementUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis19", "uis20"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis21", "uis22"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "uis23", "uis24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("USES", "IF");

        REQUIRE(
                ((result.find("uis20") != result.end()) &&
                 (result.find("uis22") != result.end()) &&
                 (result.find("uis24") != result.end())));
    }
}

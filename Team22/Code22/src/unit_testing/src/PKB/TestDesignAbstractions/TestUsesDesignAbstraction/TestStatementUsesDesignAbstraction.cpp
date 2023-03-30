//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsController.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of StatementUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us1"));

        Result expectedResult("USES:STATEMENT", "us1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("us1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent StatementUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us2"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("USES", "us2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent StatementUses Design Abstraction") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an StatementUses Design Abstraction When Multiple StatementUses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us4"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an StatementUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "us6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "us6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "us6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "us6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("WHILE", "us6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "us6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us6"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an StatementUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("STATEMENT", "us7"));

        REQUIRE(pkbResult.toString() == "USES:STATEMENT: us7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All StatementUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us13", "us14"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us15", "us16"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us17", "us18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("USES", "STATEMENT");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By StatementUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us19", "us20"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us21", "us22"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "us23", "us24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("USES", "STATEMENT");

        REQUIRE(
                ((result.find("us20") != result.end()) &&
                 (result.find("us22") != result.end()) &&
                 (result.find("us24") != result.end()))
        );
    }
}

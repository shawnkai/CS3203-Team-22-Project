//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsController.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of ProcedureCallUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc1"));

        Result expectedResult("USES:PROCEDURECALL", "updc1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("updc1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent ProcedureCallUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc2"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("USES", "updc2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ProcedureCallUses Design Abstraction") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ProcedureCallUses Design Abstraction When Multiple ProcedureCallUses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc4"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ProcedureCallUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "updc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "updc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "updc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "updc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("WHILE", "updc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "updc6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc6"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ProcedureCallUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "updc8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURECALL", "updc7"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURECALL: updc7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All ProcedureCallUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc13", "updc14"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc15", "updc16"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc17", "updc18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("USES", "PROCEDURECALL");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By ProcedureCallUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc19", "updc20"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc21", "updc22"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "updc23", "updc24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("USES", "PROCEDURECALL");

        REQUIRE(
                ((result.find("updc20") != result.end()) &&
                 (result.find("updc22") != result.end()) &&
                 (result.find("updc24") != result.end()))
        );
    }
}

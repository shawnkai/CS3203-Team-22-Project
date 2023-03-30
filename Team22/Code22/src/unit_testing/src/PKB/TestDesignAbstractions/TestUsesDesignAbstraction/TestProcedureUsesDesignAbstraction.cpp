//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsController.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of ProcedureUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd1"));

        Result expectedResult("USES:PROCEDURE", "upd1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("upd1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent ProcedureUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd2"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("USES", "upd2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ProcedureUses Design Abstraction") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ProcedureUses Design Abstraction When Multiple ProcedureUses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd4"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ProcedureUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "upd6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "upd6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "upd6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "upd6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("WHILE", "upd6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "upd6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd6"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ProcedureUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "upd8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PROCEDURE", "upd7"));

        REQUIRE(pkbResult.toString() == "USES:PROCEDURE: upd7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All ProcedureUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd13", "upd14"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd15", "upd16"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd17", "upd18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("USES", "PROCEDURE");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By ProcedureUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd19", "upd20"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd21", "upd22"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "upd23", "upd24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("USES", "PROCEDURE");

        REQUIRE(
                ((result.find("upd20") != result.end()) &&
                 (result.find("upd22") != result.end()) &&
                 (result.find("upd24") != result.end()))
        );
    }
}

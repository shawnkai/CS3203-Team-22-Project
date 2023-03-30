//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignAbstractionsController.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of PrintUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PRINT", "up1"));

        Result expectedResult("USES:PRINT", "up1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("up1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent PrintUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PRINT", "up2"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("USES", "up2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent PrintUses Design Abstraction") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PRINT", "up0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an PrintUses Design Abstraction When Multiple PrintUses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PRINT", "up4"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an PrintUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "up6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "up6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "up6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "up6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("WHILE", "up6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("IF", "up6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PRINT", "up6"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an PrintUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "up8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("USES", make_pair("PRINT", "up7"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All PrintUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up13", "up14"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up15", "up16"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up17", "up18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("USES", "PRINT");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By PrintUses Design Abstractions") {
    SECTION("") {
        DesignAbstractionsController designAbstractionsControllerTest = DesignAbstractionsController();

        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up19", "up20"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up21", "up22"));
        designAbstractionsControllerTest.addDesignAbstraction("USES", make_tuple("PRINT", "up23", "up24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("USES", "PRINT");

        REQUIRE(
                ((result.find("up20") != result.end()) &&
                 (result.find("up22") != result.end()) &&
                 (result.find("up24") != result.end()))
        );
    }
}

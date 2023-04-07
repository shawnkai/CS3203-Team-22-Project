//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "PKB/Interfaces/DesignAbstractionsInterface.h"
#include "catch.hpp"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of ProcedureCallModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc1", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc1"));

        Result expectedResult("MODIFIES:PROCEDURECALL", "mpc1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        try {
            designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("mpc1", "1"));
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent ProcedureCallModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc2", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc2", "1"));

        try {
            Result result = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", "mpc2");
        } catch (InvalidAPICallException &e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ProcedureCallModifies Design Abstraction") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc3", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ProcedureCallModifies Design Abstraction When Multiple ProcedureCallModifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc4", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc5", "1"));
        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ProcedureCallModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc6", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mpc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mpc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mpc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mpc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mpc6", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mpc6", "1"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ProcedureCallModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc7", "1"));

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc7", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc7", "2"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mpc8", "1"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc8", "3"));

        Result pkbResult = designAbstractionsControllerTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Retrieval of All ProcedureCallModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc13", "mpc14"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc15", "mpc16"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc17", "mpc18"));

        vector<Result> result = designAbstractionsControllerTest.getAllDesignAbstractions("MODIFIES", "PROCEDURECALL");

        REQUIRE(result.size() != 0);
    }
}

TEST_CASE("Test 8: Retrieval of Variables Captured By ProcedureCallModifies Design Abstractions") {
    SECTION("") {
        DesignAbstractionsInterface designAbstractionsControllerTest = DesignAbstractionsInterface();

        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc19", "mpc20"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc21", "mpc22"));
        designAbstractionsControllerTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc23", "mpc24"));

        unordered_map<string, unordered_set<string>> result =
                designAbstractionsControllerTest.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "PROCEDURECALL");

        REQUIRE(
                ((result.find("mpc20") != result.end()) &&
                 (result.find("mpc22") != result.end()) &&
                 (result.find("mpc24") != result.end())));
    }
}

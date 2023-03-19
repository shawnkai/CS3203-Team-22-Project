//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of ProcedureCallModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc1"));

        Result expectedResult("MODIFIES:PROCEDURECALL", "mpc1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        PKB pkbTest = PKB();

        try {
            pkbTest.addDesignAbstraction("MODIFIES", make_tuple("mpc1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent ProcedureCallModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        PKB pkbTest = PKB();

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc2", "1"));

        try {
            Result result = pkbTest.getDesignAbstraction("MODIFIES", "mpc2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent ProcedureCallModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an ProcedureCallModifies Design Abstraction When Multiple ProcedureCallModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an ProcedureCallModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mpc6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mpc6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mpc6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mpc6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mpc6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mpc6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an ProcedureCallModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mpc8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:PROCEDURECALL: mpc7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The ProcedureCallModifies Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc9", "mpc10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc9", "mpc10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc9", "mpc11"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc9", "mpc12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("PROCEDURECALL", "mpc9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "MODIFIES:PROCEDURECALL: mpc9: mpc10, mpc11, mpc12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

TEST_CASE("Test 9: Retrieval of All ProcedureCallModifies Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc13", "mpc14"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc15", "mpc16"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc17", "mpc18"));

        vector<Result> result = pkbTest.getAllDesignAbstractions("MODIFIES", "PROCEDURECALL");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 10: Retrieval of Variables Captured By ProcedureCallModifies Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();

        pkbTest.clearAllDatabases();

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc19", "mpc20"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc21", "mpc22"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mpc23", "mpc24"));

        unordered_map<string, unordered_set<string>> result =
                pkbTest.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "PROCEDURECALL");

        REQUIRE(result.size() == 3);
    }
}

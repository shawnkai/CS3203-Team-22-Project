//
// Created by Jai Lulla  on 18/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of IfStatementModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis1"));

        Result expectedResult("MODIFIES:IF", "mis1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        PKB pkbTest = PKB();

        try {
            pkbTest.addDesignAbstraction("MODIFIES", make_tuple("mis1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent IfStatementModifies Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis2"));

        REQUIRE(pkbResult.toString() == "MODIFIES:IF: mis2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        PKB pkbTest = PKB();

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis2", "1"));

        try {
            Result result = pkbTest.getDesignAbstraction("MODIFIES", "mis2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent IfStatementModifies Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an IfStatementModifies Design Abstraction When Multiple IfStatementModifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis4", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis4"));

        REQUIRE(pkbResult.toString() == "MODIFIES:IF: mis4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an IfStatementModifies Design Abstraction When Multiple Different Modifies Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis6", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURECALL", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("PROCEDURE", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("STATEMENT", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("ASSIGNMENT", "mis6", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("WHILE", "mis6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis6"));

        REQUIRE(pkbResult.toString() == "MODIFIES:IF: mis6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an IfStatementModifies Design Abstraction When Multiple Same Modifies Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis7", "1"));

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis7", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis7", "2"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("READ", "mis8", "1"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis7"));

        REQUIRE(pkbResult.toString() == "MODIFIES:IF: mis7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The IfStatementModifies Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis9", "mis10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis9", "mis10"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis9", "mis11"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis9", "mis12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("MODIFIES", make_pair("IF", "mis9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "MODIFIES:IF: mis9: mis10, mis11, mis12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

TEST_CASE("Test 9: Retrieval of All IfStatementModifies Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis13", "mis14"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis15", "mis16"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis17", "mis18"));

        vector<Result> result = pkbTest.getAllDesignAbstractions("MODIFIES", "IF");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 10: Retrieval of Variables Captured By IfStatementModifies Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();

        pkbTest.clearAllDatabases();

        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis19", "mis20"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis21", "mis22"));
        pkbTest.addDesignAbstraction("MODIFIES", make_tuple("IF", "mis23", "mis24"));

        unordered_map<string, unordered_set<string>> result =
                pkbTest.getAllVariablesCapturedByDesignAbstraction("MODIFIES", "IF");

        REQUIRE(result.size() == 3);
    }
}

//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/PKB.h"

#include "PKB/Exceptions/InvalidAPICallException.cpp"

using namespace std;

TEST_CASE("Test 1: Creation of PrintUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 3") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up1", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up1"));

        Result expectedResult("USES:PRINT", "up1", vector<string>{"1"});

        REQUIRE(pkbResult.areEqual(expectedResult));
    }

    SECTION("Using API With A Tuple of Size 2") {
        bool throwsException = false;
        PKB pkbTest = PKB();

        try {
            pkbTest.addDesignAbstraction("USES", make_tuple("up1", "1"));
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 2: Retrieval of an existent PrintUses Design Abstraction") {
    SECTION("Using API With A Tuple of Size 2") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up2", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up2"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up2: 1, ");
    }

    SECTION("Using API Without Tuple") {
        bool throwsException = false;
        PKB pkbTest = PKB();

        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up2", "1"));

        try {
            Result result = pkbTest.getDesignAbstraction("USES", "up2");
        } catch (InvalidAPICallException& e) {
            throwsException = true;
        }

        REQUIRE(throwsException);
    }
}

TEST_CASE("Test 3: Retrieval of a non-existent PrintUses Design Abstraction") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up3", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up0"));

        REQUIRE(pkbResult.toString() == "none: none: none, ");
    }
}

TEST_CASE("Test 4: Retrieval of an PrintUses Design Abstraction When Multiple PrintUses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up4", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up5", "1"));
        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up4"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up4: 1, ");
    }
}

TEST_CASE("Test 5: Retrieval of an PrintUses Design Abstraction When Multiple Different Uses Design Abstractions Are Stored") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up6", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURECALL", "up6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PROCEDURE", "up6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "up6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("ASSIGNMENT", "up6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("WHILE", "up6", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("IF", "up6", "1"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up6"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up6: 1, ");
    }
}

TEST_CASE("Test 6: Retrieval of an PrintUses Design Abstraction When Multiple Same Uses Design Abstractions Are Stored Including Duplicated Values") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up7", "1"));

        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up7", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up7", "2"));
        pkbTest.addDesignAbstraction("USES", make_tuple("STATEMENT", "up8", "1"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up8", "3"));

        Result pkbResult = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up7"));

        REQUIRE(pkbResult.toString() == "USES:PRINT: up7: 1, 2, ");
    }
}

TEST_CASE("Test 7: Populate The PrintUses Database And Call Clear All Database using the clearAllDatabases() API") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up9", "up10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up9", "up10"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up9", "up11"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up9", "up12"));

        Result pkbResultBeforeClearing = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up9"));

        pkbTest.clearAllDatabases();

        Result pkbResultAfterClearing = pkbTest.getDesignAbstraction("USES", make_pair("PRINT", "up9"));

        REQUIRE(((pkbResultBeforeClearing.toString() == "USES:PRINT: up9: up10, up11, up12, ")
                 && (pkbResultAfterClearing.toString() == "none: none: none, ")));
    }
}

TEST_CASE("Test 9: Retrieval of All PrintUses Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up13", "up14"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up15", "up16"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up17", "up18"));

        vector<Result> result = pkbTest.getAllDesignAbstractions("USES", "PRINT");

        REQUIRE(result.size() == 3);
    }
}

TEST_CASE("Test 10: Retrieval of Variables Captured By PrintUses Design Abstractions") {
    SECTION("") {
        PKB pkbTest = PKB();

        pkbTest.clearAllDatabases();

        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up19", "up20"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up21", "up22"));
        pkbTest.addDesignAbstraction("USES", make_tuple("PRINT", "up23", "up24"));

        unordered_map<string, unordered_set<string>> result =
                pkbTest.getAllVariablesCapturedByDesignAbstraction("USES", "PRINT");

        REQUIRE(result.size() == 3);
    }
}

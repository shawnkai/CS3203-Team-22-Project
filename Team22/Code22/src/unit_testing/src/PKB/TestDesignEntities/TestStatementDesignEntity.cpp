//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignEntitiesInterface.h"

using namespace std;

TEST_CASE("Test 1: Creation of Statement Design Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("STATEMENT", "s1");

        Result expectedResult("STATEMENT", "s1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Statement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("STATEMENT", "s2");

        Result expectedResult("STATEMENT", "s2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: Statement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("STATEMENT", "s3");

        Result expectedResult("STATEMENT", "s3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: Statement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("STATEMENT", "s0");

        Result expectedResult("STATEMENT", "s4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: Statement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "s5");

        Result expectedResult("STATEMENT", "s5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: Statement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "s0");

        Result expectedResult("STATEMENT", "s6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Statement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "s0");

        Result expectedResult("STATEMENT", "s7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: Statement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "s8");

        Result expectedResult("STATEMENT", "s8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: Statement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("STATEMENT", "s0");

        Result expectedResult("STATEMENT", "s9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: Statement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s10", "1"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s10", "1"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s10", "2"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("STATEMENT", "s10");

        Result expectedResult("STATEMENT", "s10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: Statement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s12", "1"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s12", "1"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s12", "2"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s12", "3"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s13", "1"));
        designEntitiesController.addDesignEntity("STATEMENT", make_tuple("s14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("STATEMENT");

        REQUIRE((countBeforeClearing != 0));
    }
}

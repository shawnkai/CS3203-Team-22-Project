//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignEntitiesController.h"

using namespace std;

TEST_CASE("Test 1: Creation of Constant Design Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CONSTANT", "c1");

        Result expectedResult("CONSTANT", "c1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Constant Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CONSTANT", "c2");

        Result expectedResult("CONSTANT", "c2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: Constant Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CONSTANT", "c3");

        Result expectedResult("CONSTANT", "c3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: Constant Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CONSTANT", "c0");

        Result expectedResult("CONSTANT", "c4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: Constant Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "c5");

        Result expectedResult("CONSTANT", "c5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: Constant Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "c0");

        Result expectedResult("CONSTANT", "c6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Constant Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "c0");

        Result expectedResult("CONSTANT", "c7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: Constant Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "c8");

        Result expectedResult("CONSTANT", "c8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: Constant Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CONSTANT", "c0");

        Result expectedResult("CONSTANT", "c9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: Constant Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c10", "1"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c10", "1"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c10", "2"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CONSTANT", "c10");

        Result expectedResult("CONSTANT", "c10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 12: Constant Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c12", "1"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c12", "1"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c12", "2"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c12", "3"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c13", "1"));
        designEntitiesController.addDesignEntity("CONSTANT", make_tuple("c14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("CONSTANT");

        REQUIRE((countBeforeClearing != 0));
    }
}

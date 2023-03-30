//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignEntitiesController.h"

using namespace std;

TEST_CASE("Test 1: Creation of CallStatement Design Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CALL", "cs1");

        Result expectedResult("CALL", "cs1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: CallStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CALL", "cs2");

        Result expectedResult("CALL", "cs2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: CallStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CALL", "cs3");

        Result expectedResult("CALL", "cs3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: CallStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CALL", "cs0");

        Result expectedResult("CALL", "cs4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: CallStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "cs5");

        Result expectedResult("CALL", "cs5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: CallStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "cs0");

        Result expectedResult("CALL", "cs6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: CallStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "cs0");

        Result expectedResult("CALL", "cs7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: CallStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "cs8");

        Result expectedResult("CALL", "cs8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: CallStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CALL", "cs0");

        Result expectedResult("CALL", "cs9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: CallStatement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs10", "1"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs10", "1"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs10", "2"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("CALL", "cs10");

        Result expectedResult("CALL", "cs10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: CallStatement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs12", "1"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs12", "1"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs12", "2"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs12", "3"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs13", "1"));
        designEntitiesController.addDesignEntity("CALL", make_tuple("cs14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("CALL");

        REQUIRE((countBeforeClearing != 0));
    }
}

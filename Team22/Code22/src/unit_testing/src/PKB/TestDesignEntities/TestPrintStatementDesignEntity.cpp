//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignEntitiesController.h"

using namespace std;

TEST_CASE("Test 1: Creation of PrintStatement Design Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PRINT", "ps1");

        Result expectedResult("PRINT", "ps1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: PrintStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PRINT", "ps2");

        Result expectedResult("PRINT", "ps2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: PrintStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PRINT", "ps3");

        Result expectedResult("PRINT", "ps3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: PrintStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PRINT", "ps0");

        Result expectedResult("PRINT", "ps4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: PrintStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "ps5");

        Result expectedResult("PRINT", "ps5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: PrintStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "ps0");

        Result expectedResult("PRINT", "ps6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: PrintStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "ps0");

        Result expectedResult("PRINT", "ps7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: PrintStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "ps8");

        Result expectedResult("PRINT", "ps8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: PrintStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PRINT", "ps0");

        Result expectedResult("PRINT", "ps9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: PrintStatement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps10", "1"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps10", "1"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps10", "2"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PRINT", "ps10");

        Result expectedResult("PRINT", "ps10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: PrintStatement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps12", "1"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps12", "1"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps12", "2"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps12", "3"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps13", "1"));
        designEntitiesController.addDesignEntity("PRINT", make_tuple("ps14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("PRINT");

        REQUIRE((countBeforeClearing != 0));
    }
}

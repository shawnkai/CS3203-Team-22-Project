//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "PKB/Interfaces/DesignEntitiesInterface.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test 1: Creation of AssignmentStatement Design Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("ASSIGNMENT", "as1");

        Result expectedResult("ASSIGNMENT", "as1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: AssignmentStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("ASSIGNMENT", "as2");

        Result expectedResult("ASSIGNMENT", "as2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: AssignmentStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("ASSIGNMENT", "as3");

        Result expectedResult("ASSIGNMENT", "as3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: AssignmentStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("ASSIGNMENT", "as0");

        Result expectedResult("ASSIGNMENT", "as4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: AssignmentStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "as5");

        Result expectedResult("ASSIGNMENT", "as5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: AssignmentStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "as0");

        Result expectedResult("ASSIGNMENT", "as6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: AssignmentStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "as0");

        Result expectedResult("ASSIGNMENT", "as7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: AssignmentStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "as8");

        Result expectedResult("ASSIGNMENT", "as8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: AssignmentStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("ASSIGNMENT", "as0");

        Result expectedResult("ASSIGNMENT", "as9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: AssignmentStatement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as10", "1"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as10", "1"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as10", "2"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("ASSIGNMENT", "as10");

        Result expectedResult("ASSIGNMENT", "as10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 12: AssignmentStatement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as12", "1"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as12", "1"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as12", "2"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as12", "3"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as13", "1"));
        designEntitiesController.addDesignEntity("ASSIGNMENT", make_tuple("as14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("ASSIGNMENT");

        REQUIRE((countBeforeClearing != 0));
    }
}

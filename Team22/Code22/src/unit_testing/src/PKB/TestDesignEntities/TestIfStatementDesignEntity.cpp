//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignEntitiesInterface.h"

using namespace std;

TEST_CASE("Test 1: Creation of IfStatement Design Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("IF", "is1");

        Result expectedResult("IF", "is1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: IfStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("IF", "is2");

        Result expectedResult("IF", "is2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: IfStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("IF", "is3");

        Result expectedResult("IF", "is3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: IfStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("IF", "is0");

        Result expectedResult("IF", "is4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: IfStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "is5");

        Result expectedResult("IF", "is5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: IfStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "is0");

        Result expectedResult("IF", "is6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: IfStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "is0");

        Result expectedResult("IF", "is7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: IfStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "is8");

        Result expectedResult("IF", "is8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: IfStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("IF", "is0");

        Result expectedResult("IF", "is9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: IfStatement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is10", "1"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is10", "1"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is10", "2"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("IF", "is10");

        Result expectedResult("IF", "is10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: IfStatement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("IF", make_tuple("is12", "1"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is12", "1"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is12", "2"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is12", "3"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is13", "1"));
        designEntitiesController.addDesignEntity("IF", make_tuple("is14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("IF");

        REQUIRE((countBeforeClearing != 0));
    }
}

//
// Created by Jai Lulla  on 16/2/23.
//

#include <iostream>

#include "PKB/Interfaces/DesignEntitiesInterface.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test 1: Creation of Procedure Design Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "p1");

        Result expectedResult("PROCEDURE", "p1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Procedure Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "p2");

        Result expectedResult("PROCEDURE", "p2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: Procedure Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "p3");

        Result expectedResult("PROCEDURE", "p3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: Procedure Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "p0");

        Result expectedResult("PROCEDURE", "p4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: Procedure Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "p5");

        Result expectedResult("PROCEDURE", "p5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: Procedure Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "p0");

        Result expectedResult("PROCEDURE", "p6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Procedure Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "p0");

        Result expectedResult("PROCEDURE", "p7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: Procedure Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "p8");

        Result expectedResult("PROCEDURE", "p8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: Procedure Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "p0");

        Result expectedResult("PROCEDURE", "p9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: Procedure Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p10", "1"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p10", "1"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p10", "2"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "p10");

        Result expectedResult("PROCEDURE", "p10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: Procedure Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesInterface designEntitiesController = DesignEntitiesInterface();
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p12", "1"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p12", "1"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p12", "2"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p12", "3"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p13", "1"));
        designEntitiesController.addDesignEntity("PROCEDURE", make_tuple("p14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("PROCEDURE");

        REQUIRE((countBeforeClearing != 0));
    }
}

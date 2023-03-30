//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignEntitiesController.h"

using namespace std;

TEST_CASE("Test 1: Creation of ReadStatement Design Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("READ", "rs1");

        Result expectedResult("READ", "rs1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: ReadStatement Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("READ", "rs2");

        Result expectedResult("READ", "rs2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: ReadStatement Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("READ", "rs3");

        Result expectedResult("READ", "rs3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: ReadStatement Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("READ", "rs0");

        Result expectedResult("READ", "rs4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: ReadStatement Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "rs5");

        Result expectedResult("READ", "rs5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: ReadStatement Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "rs0");

        Result expectedResult("READ", "rs6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: ReadStatement Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "rs0");

        Result expectedResult("READ", "rs7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: ReadStatement Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "rs8");

        Result expectedResult("READ", "rs8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: ReadStatement Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("READ", "rs0");

        Result expectedResult("READ", "rs9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: ReadStatement Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs10", "1"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs10", "1"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs10", "2"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("READ", "rs10");

        Result expectedResult("READ", "rs10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: ReadStatement Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("READ", make_tuple("rs12", "1"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs12", "1"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs12", "2"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs12", "3"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs13", "1"));
        designEntitiesController.addDesignEntity("READ", make_tuple("rs14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("READ");

        REQUIRE((countBeforeClearing != 0));
    }
}

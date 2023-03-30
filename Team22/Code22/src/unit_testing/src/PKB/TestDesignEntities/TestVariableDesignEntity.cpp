//
// Created by Jai Lulla  on 17/2/23.
//

#include <iostream>

#include "catch.hpp"
#include "PKB/Interfaces/DesignEntitiesController.h"

using namespace std;

TEST_CASE("Test 1: Creation of Variable Design Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var1", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "var1");

        Result expectedResult("VARIABLE", "var1", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 2: Variable Design Entity, Query for Same Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var2", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "var2");

        Result expectedResult("VARIABLE", "var2", vector<string>{"1"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 3: Variable Design Entity, Query for Same Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var3", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "var3");

        Result expectedResult("VARIABLE", "var3", vector<string>{"2"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 4: Variable Design Entity, Query for Same Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var4", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "var0");

        Result expectedResult("VARIABLE", "var4", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 5: Variable Design Entity, Query for Different Type, Same Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("v5", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "var5");

        Result expectedResult("VARIABLE", "var5", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 6: Variable Design Entity, Query for Different Type, Different Entity Name, Same Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var6", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "var0");

        Result expectedResult("VARIABLE", "var6", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 7: Variable Design Entity, Query for Different Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var7", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "var0");

        Result expectedResult("VARIABLE", "var7", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 8: Variable Design Entity, Query for Different Type, Same Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var8", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("PROCEDURE", "var8");

        Result expectedResult("VARIABLE", "var8", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 9: Variable Design Entity, Query for Same Type, Different Entity Name, Different Occurrence") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var9", "1"));
        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "var0");

        Result expectedResult("VARIABLE", "var9", vector<string>{"1"});

        REQUIRE(!DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 10: Variable Design Entity, Check for Duplication Filtering When Multiple Occurrences Are Added") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var10", "1"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var10", "1"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var10", "2"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var11", "3"));

        Result DesignEntitiesControllerResult = designEntitiesController.getDesignEntity("VARIABLE", "var10");

        Result expectedResult("VARIABLE", "var10", vector<string>{"1", "2"});

        REQUIRE(DesignEntitiesControllerResult.areEqual(expectedResult));
    }
}

TEST_CASE("Test 11: Variable Design Entity, Populate The Database And Count The Number of Occurrences Of That Entity") {
    SECTION("") {
        DesignEntitiesController designEntitiesController = DesignEntitiesController();
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var12", "1"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var12", "1"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var12", "2"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var12", "3"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var13", "1"));
        designEntitiesController.addDesignEntity("VARIABLE", make_tuple("var14", "1"));

        int countBeforeClearing = designEntitiesController.getNumberOfDesignEntity("VARIABLE");

        REQUIRE((countBeforeClearing != 0));
    }
}

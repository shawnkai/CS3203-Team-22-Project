//
// Created by Jai Lulla  on 30/1/23.
//

#include "catch.hpp"
#include "PKB.h"

//class TestDemo {
//public:
//    void startTesting() {
//
//
//    }
//};

TEST_CASE("Test 1: Get Variable Name From PKB") {
    PKB pkb;

    SECTION("Get Variable a") {
        INFO("Test case 1 start");
        REQUIRE(pkb.getVariableName("a").compare("a") == 0);
        INFO("Test case 1 end");
    }

    SECTION("Get Variable b") {
        INFO("Test case 2 start");
        REQUIRE(pkb.getVariableName("b").compare("b") == 0);
        INFO("Test case 2 end");
    }

    SECTION("Get Variables that do not match") {
        INFO("Test case 3 start");
        REQUIRE(pkb.getVariableName("b").compare("a") > 0);
        INFO("Test case 3 end");
    }

    SECTION("Get Easter Egg") {
        INFO("Test case 4 start");
        REQUIRE(pkb.getVariableName("3a513r3gg").compare("You Cracked it!") == 0);
        INFO("Test case 4 end");
    }
}

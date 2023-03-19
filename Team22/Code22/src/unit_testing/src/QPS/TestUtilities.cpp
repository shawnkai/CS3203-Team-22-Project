//
// Created by Tanishq Sharma on 15/3/23.
//

#include "catch.hpp"
#include "Utilities.h"

using namespace std;



TEST_CASE("TestCase1_checkInfixExpression") {
    REQUIRE(Utilities::checkInfixExpression("1 "));
    REQUIRE_FALSE(Utilities::checkInfixExpression(" +temp"));
    REQUIRE(Utilities::checkInfixExpression("temp + (2 % (y - z)) * 2"));
    REQUIRE_FALSE(Utilities::checkInfixExpression("temp + (2 % (y - z) * 2"));
    REQUIRE_FALSE(Utilities::checkInfixExpression("temp + (2 % (y -- z) * 2"));
    REQUIRE_FALSE(Utilities::checkInfixExpression("temp + (2& % (y - z) * 2"));
}

